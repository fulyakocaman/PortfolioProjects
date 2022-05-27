#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include "../emergency.hpp"
#include "gtest_ext.h"

using ::testing::ContainsRegex;
using ::testing::HasSubstr;
using ::testing::Not;

class SaveFile : public UnitTestFileManager {
protected:
  SaveFile() : UnitTestFileManager("save.txt") {}
  void SetUp() override {
    UnitTestFileManager::SetUp();
    emergencies[0] = new Emergency("Wildland Fire", "Beaumont", 922);
    emergencies[1] = new MultipleEmergency("Camp Fire", "Missing person",
                                           "Butte County", 945);
    emergencies[2] = new Emergency("Vegetation Fire", "Aguanga", 1602);
  }
  Emergency* emergencies[3];
};

class DriverSaveFile : public SaveFile {};

class LoadFile : public UnitTestFileManager {
protected:
  LoadFile() : UnitTestFileManager("load.txt") {}
  void SetUp() override {
    UnitTestFileManager::SetUp();
    emergencies[0] = new Emergency("Wildland Fire", "Beaumont", 922);
    emergencies[1] = new MultipleEmergency("Camp Fire", "Missing person",
                                           "Butte County", 945);
    emergencies[2] = new Emergency("Vegetation Fire", "Aguanga", 1602);
  }
  Emergency* emergencies[3];
};

class DriverLoadFile : public LoadFile {
protected:
  void SetUp() override {
    LoadFile::SetUp();
    std::ofstream out_file("load.txt");
    out_file << 3 << "\n";
    for (int i = 0; i < 3; i++) {
      if (i == 0 || i == 2) {
        out_file << "[Emergency]\n";
        out_file << emergencies[i]->description() << "\n";
        out_file << emergencies[i]->location() << "\n";
        out_file << emergencies[i]->report_time() << "\n";
      } else {
        out_file << "[MultipleEmergency]\n";
        out_file << emergencies[i]->description() << "\n";
        out_file << ((MultipleEmergency*)emergencies[i])->other_emergencies()
                 << "\n";
        out_file << emergencies[i]->location() << "\n";
        out_file << emergencies[i]->report_time() << "\n";
      }
    }
    out_file.close();
  }
};

class DisplayEmergencies : public ::testing::Test {
protected:
  void SetUp() override {
    emergencies[0] = new Emergency("Wildland Fire", "Beaumont", 922);
    emergencies[1] = new MultipleEmergency("Camp Fire", "Missing person",
                                           "Butte County", 945);
    emergencies[2] = new Emergency("Vegetation Fire", "Aguanga", 1602);
  }

  Emergency* emergencies[3];
};

class PriorityEmergency : public DisplayEmergencies {
protected:
  void SetUp() override {
    DisplayEmergencies::SetUp();
    earliest_first[0] = emergencies[1];
    earliest_first[1] = emergencies[0];
    earliest_first[2] = emergencies[2];

    earliest_second[0] = emergencies[2];
    earliest_second[1] = emergencies[1];
    earliest_second[2] = emergencies[0];

    earliest_last[0] = emergencies[0];
    earliest_last[1] = emergencies[2];
    earliest_last[2] = emergencies[1];
  }

  Emergency* earliest_first[3];
  Emergency* earliest_second[3];
  Emergency* earliest_last[3];
};

TEST(EmergencyClass, DescriptionAccessorMutator) {
  Emergency your_emergency;
  std::string description = "Wildland Fire";
  your_emergency.set_description(description);
  ASSERT_EQ(your_emergency.description(), "Wildland Fire")
      << "Hint: The mutator was used to set the description to Wildland Fire "
         "so the accessor needs to return the same value.";
}

TEST(EmergencyClass, LocationAccessorMutator) {
  Emergency your_emergency;
  std::string location = "Beaumont";
  your_emergency.set_location(location);
  ASSERT_EQ(your_emergency.location(), "Beaumont")
      << "Hint: The mutator was used to set the location to Beaumontso the "
         "accessor needs to return the same value.";
}

TEST(EmergencyClass, ReportTimeAccessorMutator) {
  Emergency your_emergency;
  your_emergency.set_report_time(922);
  ASSERT_EQ(your_emergency.report_time(), 922)
      << "Hint: The mutator was used to set the report time to 922 the "
         "accessor needs to return the same value.";
}

TEST(EmergencyClass, DefaultConstructor) {
  Emergency your_emergency;
  ASSERT_EQ(your_emergency.description(), "None")
      << "Hint: The default description should be None.";
  ASSERT_EQ(your_emergency.location(), "None")
      << "Hint: The default location should be None";
  ASSERT_EQ(your_emergency.report_time(), 800)
      << "Hint: The default report time should be 800.";
}

TEST(EmergencyClass, NonDefaultConstructor) {
  Emergency your_emergency("Power outage", "Chino", 1430);
  ASSERT_EQ(your_emergency.description(), "Power outage")
      << "Hint: The nondefault description should be set to Power outage.";
  ASSERT_EQ(your_emergency.location(), "Chino")
      << "Hint: The nondefault location should be set to Chino";
  ASSERT_EQ(your_emergency.report_time(), 1430)
      << "Hint: The nondefault report time should be set to 1430.";
}

TEST(EmergencyManager, DefaultConstructor) {
  EmergencyManager your_emergency_manager;
}

TEST(EmergencyManager, Add) {
  EmergencyManager your_emergency_manager;
  Emergency* your_emergency = new Emergency;
  your_emergency_manager.add(your_emergency);
}

TEST(RouteManager, AddCheckedRoute) {
  EmergencyManager your_emergency_manager;
  MultipleEmergency* your_multiple_emergency = new MultipleEmergency;
  your_emergency_manager.add(your_multiple_emergency);
}

TEST(EmergencyClass, Display) {
  Emergency your_emergency;
  your_emergency.set_description("Wildland Fire");
  your_emergency.set_location("Beaumont");
  your_emergency.set_report_time(922);
  ASSERT_DURATION_LE(
      3, {SIMULATE_SIO("", your_emergency.display(), {
        ASSERT_THAT(your_output, HasSubstr("Wildland Fire"))
            << "Hint: The member function should display the emergency's "
               "description, Wildland Fire, on the screen.";
        ASSERT_THAT(your_output, HasSubstr("Beaumont"))
            << "Hint: The member function should display the emergency's "
               "location, Beaumont, on the screen.";
        ASSERT_THAT(your_output, HasSubstr("922"))
            << "Hint: The member function should display the emergency's "
               "report time, 922, on the screen.";
      })})
}

TEST(EmergencyClass, SaveString) {
  Emergency your_emergency;
  your_emergency.set_description("Wildland Fire");
  your_emergency.set_location("Beaumont");
  your_emergency.set_report_time(922);
  ASSERT_THAT(your_emergency.save_string(), HasSubstr("[Emergency]"))
      << "Hint: The member function should return the emergency's type, "
         "[Emergency], on the screen.";
  ASSERT_THAT(your_emergency.save_string(), HasSubstr("Wildland Fire"))
      << "Hint: The member function should return the emergency's description, "
         "Wildland Fire, on the screen.";
  ASSERT_THAT(your_emergency.save_string(), HasSubstr("Beaumont"))
      << "Hint: The member function should return the emergency's location, "
         "Beaumont, on the screen.";
  ASSERT_THAT(your_emergency.save_string(), HasSubstr("922"))
      << "Hint: The member function should return the emergency's report time, "
         "922, on the screen.";
}

TEST(MultipleEmergency, SaveString) {
  MultipleEmergency your_multiple_emergency("Camp Fire", "Missing person",
                                            "Butte County", 945);
  ASSERT_THAT(your_multiple_emergency.save_string(),
              HasSubstr("[MultipleEmergency]"))
      << "Hint: The member function should return the emergency's type, "
         "[MultipleEmergency], on the screen.";
  ASSERT_THAT(your_multiple_emergency.save_string(), HasSubstr("Camp Fire"))
      << "Hint: The member function should return the emergency's description, "
         "Camp Fire, on the screen.";
  ASSERT_THAT(your_multiple_emergency.save_string(),
              HasSubstr("Missing person"))
      << "Hint: The member function should return the emergency's other "
         "emergencies, Missing person, on the screen.";
  ASSERT_THAT(your_multiple_emergency.save_string(), HasSubstr("Butte County"))
      << "Hint: The member function should return the emergency's location, "
         "Butte County, on the screen.";
  ASSERT_THAT(your_multiple_emergency.save_string(), HasSubstr("945"))
      << "Hint: The member function should return the emergency's report time, "
         "945, on the screen.";
}

TEST(MultipleEmergency, Inheritance) {
  MultipleEmergency your_multiple_emergency;
  Emergency* your_emergency =
      dynamic_cast<Emergency*>(&your_multiple_emergency);
  ASSERT_NE(your_emergency, nullptr)
      << "The MultipleEmergency class should inherit from the Emergency class.";
}

TEST(MultipleEmergency, AccessorsMutators) {
  MultipleEmergency your_multiple_emergency;
  your_multiple_emergency.set_other_emergencies("Missing person");
  ASSERT_EQ(your_multiple_emergency.other_emergencies(), "Missing person")
      << "Hint: The mutator was used to set the take off time to Missing "
         "person so the accessor needs to return the same value.";
}

TEST(MultipleEmergency, DefaultConstructor) {
  MultipleEmergency your_multiple_emergency;
  ASSERT_EQ(your_multiple_emergency.description(), "None")
      << "Hint: The default description should be None.";
  ASSERT_EQ(your_multiple_emergency.other_emergencies(), "None")
      << "Hint: The default other emergencies should be None.";
  ASSERT_EQ(your_multiple_emergency.location(), "None")
      << "Hint: The default location should be None";
  ASSERT_EQ(your_multiple_emergency.report_time(), 800)
      << "Hint: The default report time should be 800.";
}

TEST(MultipleEmergency, NonDefaultConstructor) {
  MultipleEmergency your_multiple_emergency("Camp Fire", "Missing person",
                                            "Butte County", 945);
  ASSERT_EQ(your_multiple_emergency.description(), "Camp Fire")
      << "Hint: The nondefault description should be set to Camp Fire.";
  ASSERT_EQ(your_multiple_emergency.other_emergencies(), "Missing person")
      << "Hint: The nondefault other emergencies should be Missing person.";
  ASSERT_EQ(your_multiple_emergency.location(), "Butte County")
      << "Hint: The nondefault location should be set to Butte County";
  ASSERT_EQ(your_multiple_emergency.report_time(), 945)
      << "Hint: The nondefault report time should be set to 945.";
}

TEST(MultipleEmergency, Display) {
  MultipleEmergency your_multiple_emergency("Camp Fire", "Missing person",
                                            "Butte County", 945);
  ASSERT_DURATION_LE(
      3, {SIMULATE_SIO("", your_multiple_emergency.display(), {
        ASSERT_THAT(your_output, HasSubstr("Camp Fire"))
            << "Hint: The member function should display the multiple "
               "emergency's description, Camp Fire.";
        ASSERT_THAT(your_output, HasSubstr("Missing person"))
            << "Hint: The member function should display the multiple "
               "emergency's other emergencies, Missing person.";
        ASSERT_THAT(your_output, HasSubstr("Butte County"))
            << "Hint: The member function should display the multiple "
               "emergency's location, Butte County";
        ASSERT_THAT(your_output, HasSubstr("945"))
            << "Hint: The member function should display the multiple "
               "emergency's report time, 945.";
      })})
}

//
TEST(PotentialEmergency, Inheritance) {
  PotentialEmergency your_potential_emergency;
  Emergency* your_emergency =
      dynamic_cast<Emergency*>(&your_potential_emergency);
  ASSERT_NE(your_emergency, nullptr)
      << "The MultipleEmergency class should inherit from the Emergency class.";
}

TEST(PotentialEmergency, AccessorsMutators) {
  PotentialEmergency your_potential_emergency;
  your_potential_emergency.set_estimated_time(500);
  ASSERT_EQ(your_potential_emergency.estimated_time(), 500)
      << "Hint: The mutator was used to set the estimated time to 500 so the "
         "accessor needs to return the same value.";
}

TEST(PotentialEmergency, DefaultConstructor) {
  PotentialEmergency your_potential_emergency;
  ASSERT_EQ(your_potential_emergency.description(), "None")
      << "Hint: The default description should be None.";
  ASSERT_EQ(your_potential_emergency.location(), "None")
      << "Hint: The default location should be None";
  ASSERT_EQ(your_potential_emergency.estimated_time(), 1000)
      << "Hint: The default estimated time should be 1000.";
  ASSERT_EQ(your_potential_emergency.report_time(), 800)
      << "Hint: The default report time should be 800.";
}

TEST(PotentialEmergency, NonDefaultConstructor) {
  PotentialEmergency your_potential_emergency("Flood", "Tonto Basin", 2000,
                                              1327);
  ASSERT_EQ(your_potential_emergency.description(), "Flood")
      << "Hint: The nondefault description should be set to Flood.";
  ASSERT_EQ(your_potential_emergency.location(), "Tonto Basin")
      << "Hint: The nondefault location should be set to Tonto Basin";
  ASSERT_EQ(your_potential_emergency.estimated_time(), 2000)
      << "Hint: The nondefault estimated time should be set to 2000.";
  ASSERT_EQ(your_potential_emergency.report_time(), 1327)
      << "Hint: The nondefault report time should be set to 1327.";
}

TEST(PotentialEmergency, Display) {
  PotentialEmergency your_potential_emergency("Flood", "Tonto Basin", 2000,
                                              1327);
  ASSERT_DURATION_LE(3, {SIMULATE_SIO("", your_potential_emergency.display(), {
                       ASSERT_THAT(your_output, HasSubstr("Flood"))
                           << "Hint: The member function should display the "
                              "potential emergency's description, Flood.";
                       ASSERT_THAT(your_output, HasSubstr("Tonto Basin"))
                           << "Hint: The member function should display the "
                              "potential emergency's location, Tonto Basin";
                       ASSERT_THAT(your_output, HasSubstr("2000"))
                           << "Hint: The member function should display the "
                              "potential emergency's estimated time, 2000.";
                       ASSERT_THAT(your_output, HasSubstr("1327"))
                           << "Hint: The member function should display the "
                              "potential emergency's report time, 1327.";
                     })})
}

TEST(PotentialEmergency, SaveString) {
  PotentialEmergency your_potential_emergency("Flood", "Tonto Basin", 2000,
                                              1327);
  ASSERT_THAT(your_potential_emergency.save_string(),
              HasSubstr("[PotentialEmergency]"))
      << "Hint: The member function should return the emergency's type, "
         "[PotentialEmergency], on the screen.";
  ASSERT_THAT(your_potential_emergency.save_string(), HasSubstr("Flood"))
      << "Hint: The member function should return the emergency's description, "
         "Floode, on the screen.";
  ASSERT_THAT(your_potential_emergency.save_string(), HasSubstr("Tonto Basin"))
      << "Hint: The member function should return the emergency's location, "
         "Tonto Basin, on the screen.";
  ASSERT_THAT(your_potential_emergency.save_string(), HasSubstr("2000"))
      << "Hint: The member function should return the emergency's estimated "
         "time, 2000, on the screen.";
  ASSERT_THAT(your_potential_emergency.save_string(), HasSubstr("1327"))
      << "Hint: The member function should return the emergency's report time, "
         "1327, on the screen.";
}
//

TEST(CreateEmergency, CheckDescription) {
  Emergency* your_emergency;
  SIMULATE_CIN("Magnitude 5.0 Earthquake\nLittle Lake\n2049\n",
               { your_emergency = create_emergency(); });
  ASSERT_EQ(your_emergency->description(), "Magnitude 5.0 Earthquake")
      << "Hint: The function should assign Wildland Fire as the description "
         "for the Emergency object.";
  delete your_emergency;
}

TEST(CreateEmergency, CheckLocation) {
  Emergency* your_emergency;
  SIMULATE_CIN("Magnitude 5.0 Earthquake\nLittle Lake\n2049\n",
               { your_emergency = create_emergency(); });
  ASSERT_EQ(your_emergency->location(), "Little Lake")
      << "Hint: The function should assign Little Lake as the location for the "
         "Emergency object.";
  delete your_emergency;
}

TEST(CreateEmergency, CheckReportTime) {
  Emergency* your_emergency;
  SIMULATE_CIN("Magnitude 5.0 Earthquake\nLittle Lake\n2049\n",
               { your_emergency = create_emergency(); });
  ASSERT_EQ(your_emergency->report_time(), 2049)
      << "Hint: The function should assign 2049 as the report time for the "
         "Emergency object.";
  delete your_emergency;
}

TEST(CreateMultipleEmergency, CheckDescription) {
  MultipleEmergency* your_multiple_emergency;
  SIMULATE_CIN("Camp Fire\nMissing person\nButte County\n945\n",
               { your_multiple_emergency = create_multiple_emergency(); });
  ASSERT_EQ(your_multiple_emergency->description(), "Camp Fire")
      << "Hint: The function should assign Camp Fire as the description for "
         "the MultipleEmergency object.";
  delete your_multiple_emergency;
}

TEST(CreateMultipleEmergency, CheckOtherEmergencies) {
  MultipleEmergency* your_multiple_emergency;
  SIMULATE_CIN("Camp Fire\nMissing person\nButte County\n945\n",
               { your_multiple_emergency = create_multiple_emergency(); });
  ASSERT_EQ(your_multiple_emergency->other_emergencies(), "Missing person")
      << "Hint: The function should assign Missing person as the other "
         "emergencies for the MultipleEmergency object.";
  delete your_multiple_emergency;
}

TEST(CreateMultipleEmergency, CheckLocation) {
  MultipleEmergency* your_multiple_emergency;
  SIMULATE_CIN("Camp Fire\nMissing person\nButte County\n945\n",
               { your_multiple_emergency = create_multiple_emergency(); });
  ASSERT_EQ(your_multiple_emergency->location(), "Butte County")
      << "Hint: The function should assign Butte County as the location for "
         "the MultipleEmergency object.";
  delete your_multiple_emergency;
}

TEST(CreateMultipleEmergency, CheckReportTime) {
  MultipleEmergency* your_multiple_emergency;
  SIMULATE_CIN("Camp Fire\nMissing person\nButte County\n945\n",
               { your_multiple_emergency = create_multiple_emergency(); });
  ASSERT_EQ(your_multiple_emergency->report_time(), 945)
      << "Hint: The function should assign 945 as the report time for the "
         "MultipleEmergency object.";
  delete your_multiple_emergency;
}
//
TEST(CreatePotentialEmergency, CheckDescription) {
  PotentialEmergency* your_potential_emergency;
  SIMULATE_CIN("Flood\nTonto Basin\n2000\n1327\n",
               { your_potential_emergency = create_potential_emergency(); });
  ASSERT_EQ(your_potential_emergency->description(), "Flood")
      << "Hint: The function should assign Flood as the description for the "
         "PotentialEmergency object.";
  delete your_potential_emergency;
}

TEST(CreatePotentialEmergency, CheckLocation) {
  PotentialEmergency* your_potential_emergency;
  SIMULATE_CIN("Flood\nTonto Basin\n2000\n1327\n",
               { your_potential_emergency = create_potential_emergency(); });
  ASSERT_EQ(your_potential_emergency->location(), "Tonto Basin")
      << "Hint: The function should assign Tonto Basin as the location for the "
         "PotentialEmergency object.";
  delete your_potential_emergency;
}

TEST(CreatePotentialEmergency, CheckEstimatedTime) {
  PotentialEmergency* your_potential_emergency;
  SIMULATE_CIN("Flood\nTonto Basin\n2000\n1327\n",
               { your_potential_emergency = create_potential_emergency(); });
  ASSERT_EQ(your_potential_emergency->estimated_time(), 2000)
      << "Hint: The function should assign 2000 as the estimated time for the "
         "PotentialEmergency object.";
  delete your_potential_emergency;
}

TEST(CreatePotentialEmergency, CheckReportTime) {
  PotentialEmergency* your_potential_emergency;
  SIMULATE_CIN("Flood\nTonto Basin\n2000\n1327\n",
               { your_potential_emergency = create_potential_emergency(); });
  ASSERT_EQ(your_potential_emergency->report_time(), 1327)
      << "Hint: The function should assign 1327 as the report time for the "
         "PotentialEmergency object.";
  delete your_potential_emergency;
}
//

TEST_F(DisplayEmergencies, OneEmergency) {
  EmergencyManager your_emergency_manager;
  your_emergency_manager.add(emergencies[0]);
  ASSERT_DURATION_LE(
      3, {SIMULATE_SIO("", your_emergency_manager.display_emergencies(), {
        ASSERT_THAT(your_output, HasSubstr("Wildland Fire"))
            << "Hint: The member function should display the first emergency's "
               "description, Wildland Fire, on the screen.";
        ASSERT_THAT(your_output, HasSubstr("Beaumont"))
            << "Hint: The member function should display the first emergency's "
               "location, Beaumont, on the screen.";
        ASSERT_THAT(your_output, HasSubstr("922"))
            << "Hint: The member function should display the first emergency's "
               "report time, 922, on the screen.";

        ASSERT_THAT(your_output, Not(HasSubstr("Camp Fire")))
            << "Hint: The member function should not display other emergency's "
               "description.";
        ASSERT_THAT(your_output, Not(HasSubstr("Missing person")))
            << "Hint: The member function should not display other emergency's "
               "other emergencies.";
        ASSERT_THAT(your_output, Not(HasSubstr("Butte County")))
            << "Hint: The member function should not display other emergency's "
               "location.";
        ASSERT_THAT(your_output, Not(HasSubstr("945")))
            << "Hint: The member function should not display other emergency's "
               "report time.";

        ASSERT_THAT(your_output, Not(HasSubstr("Vegetation Fire")))
            << "Hint: The member function should not display other emergency's "
               "description.";
        ASSERT_THAT(your_output, Not(HasSubstr("Aguanga")))
            << "Hint: The member function should not display other emergency's "
               "location.";
        ASSERT_THAT(your_output, Not(HasSubstr("1602")))
            << "Hint: The member function should not display other emergency's "
               "report time.";
      })})
}

TEST_F(DisplayEmergencies, MultipleEmergency) {
  EmergencyManager your_emergency_manager;
  your_emergency_manager.add(emergencies[0]);
  your_emergency_manager.add(emergencies[1]);
  your_emergency_manager.add(emergencies[2]);
  ASSERT_DURATION_LE(
      3, {SIMULATE_SIO("", your_emergency_manager.display_emergencies(), {
        ASSERT_THAT(your_output, HasSubstr("Wildland Fire"))
            << "Hint: The member function should display the first emergency's "
               "description, Wildland Fire, on the screen.";
        ASSERT_THAT(your_output, HasSubstr("Beaumont"))
            << "Hint: The member function should display the first emergency's "
               "location, Beaumont, on the screen.";
        ASSERT_THAT(your_output, HasSubstr("922"))
            << "Hint: The member function should display the first emergency's "
               "report time, 922, on the screen.";

        ASSERT_THAT(your_output, HasSubstr("Camp Fire"))
            << "Hint: The member function should display other emergency's "
               "description.";
        ASSERT_THAT(your_output, HasSubstr("Missing person"))
            << "Hint: The member function should display other emergency's "
               "other emergencies.";
        ASSERT_THAT(your_output, HasSubstr("Butte County"))
            << "Hint: The member function should display other emergency's "
               "location.";
        ASSERT_THAT(your_output, HasSubstr("945"))
            << "Hint: The member function should display other emergency's "
               "report time.";

        ASSERT_THAT(your_output, HasSubstr("Vegetation Fire"))
            << "Hint: The member function should display other emergency's "
               "description.";
        ASSERT_THAT(your_output, HasSubstr("Aguanga"))
            << "Hint: The member function should display other emergency's "
               "location.";
        ASSERT_THAT(your_output, HasSubstr("1602"))
            << "Hint: The member function should display other emergency's "
               "report time.";
      })})
}

TEST(GetCurrentTime, Time1) {
  unsigned short int your_result = 0;
  SIMULATE_SIO("2200", your_result = get_current_time(), {
    ASSERT_THAT(your_result, 2200)
        << "Hint: The function should return the value provided by the user.";
  })
}

TEST(GetCurrentTime, Time2) {
  unsigned short int your_result = 0;
  SIMULATE_SIO("1141", your_result = get_current_time(), {
    ASSERT_THAT(your_result, 1141)
        << "Hint: The function should return the value provided by the user.";
  })
}

TEST_F(PriorityEmergency, NoEmergencies) {
  EmergencyManager your_emergency_manager;
  SIMULATE_SIO("", your_emergency_manager.show_priority_emergency(1000), {
    ASSERT_THAT(your_output,
                ContainsRegex(R"(.*(no emergencies|No emergencies).*)"))
        << "Hint: The function should say that no emergencies were reported.";
  })
}

TEST_F(PriorityEmergency, PriorityEmergencyFirst) {
  EmergencyManager your_emergency_manager;
  your_emergency_manager.add(earliest_first[0]);
  your_emergency_manager.add(earliest_first[1]);
  your_emergency_manager.add(earliest_first[2]);
  SIMULATE_SIO("", your_emergency_manager.show_priority_emergency(1000), {
    ASSERT_THAT(your_output, HasSubstr("Wildland Fire"))
        << "Your program should show the earliest emergency's description "
           "Wildland Fire.";
    ASSERT_THAT(your_output, HasSubstr("Beaumont"))
        << "Your program should show the created emergency's location, "
           "Beaumont.";
    ASSERT_THAT(your_output, HasSubstr("922"))
        << "Your program should show the created emergency's report time 922.";
  })
}

TEST_F(PriorityEmergency, PriorityEmergencySecond) {
  EmergencyManager your_emergency_manager;
  your_emergency_manager.add(earliest_second[0]);
  your_emergency_manager.add(earliest_second[1]);
  your_emergency_manager.add(earliest_second[2]);
  SIMULATE_SIO("", your_emergency_manager.show_priority_emergency(1000), {
    ASSERT_THAT(your_output, HasSubstr("Wildland Fire"))
        << "Your program should show the earliest emergency's description "
           "Wildland Fire.";
    ASSERT_THAT(your_output, HasSubstr("Beaumont"))
        << "Your program should show the created emergency's location, "
           "Beaumont.";
    ASSERT_THAT(your_output, HasSubstr("922"))
        << "Your program should show the created emergency's report time 922.";
  })
}

TEST_F(PriorityEmergency, PriorityEmergencyLast) {
  EmergencyManager your_emergency_manager;
  your_emergency_manager.add(earliest_last[0]);
  your_emergency_manager.add(earliest_last[1]);
  your_emergency_manager.add(earliest_last[2]);
  SIMULATE_SIO("", your_emergency_manager.show_priority_emergency(1000), {
    ASSERT_THAT(your_output, HasSubstr("Wildland Fire"))
        << "Your program should show the earliest emergency's description "
           "Wildland Fire.";
    ASSERT_THAT(your_output, HasSubstr("Beaumont"))
        << "Your program should show the created emergency's location, "
           "Beaumont.";
    ASSERT_THAT(your_output, HasSubstr("922"))
        << "Your program should show the created emergency's report time 922.";
  })
}

TEST_F(PriorityEmergency, NoHourDiffNoMinDiff) {
  EmergencyManager your_emergency_manager;
  your_emergency_manager.add(earliest_first[0]);
  your_emergency_manager.add(earliest_first[1]);
  your_emergency_manager.add(earliest_first[2]);
  SIMULATE_SIO("", your_emergency_manager.show_priority_emergency(922), {
    ASSERT_THAT(your_output, ContainsRegex(R"(0.h(r|our))"))
        << "Your program should show no difference in hours.";
    ASSERT_THAT(your_output, ContainsRegex(R"(0.min)"))
        << "Your program should show no difference in minutes.";
  })
}

TEST_F(PriorityEmergency, NoHourDiffMinDiff) {
  EmergencyManager your_emergency_manager;
  your_emergency_manager.add(earliest_first[0]);
  your_emergency_manager.add(earliest_first[1]);
  your_emergency_manager.add(earliest_first[2]);
  SIMULATE_SIO("", your_emergency_manager.show_priority_emergency(947), {
    ASSERT_THAT(your_output, ContainsRegex(R"(0.h(r|our))"))
        << "Your program should show no difference in hours.";
    ASSERT_THAT(your_output, ContainsRegex(R"(25.min)"))
        << "Your program should show a 25 minute difference.";
  })
}

TEST_F(PriorityEmergency, NoHourDiffMinDiff2) {
  EmergencyManager your_emergency_manager;
  your_emergency_manager.add(earliest_first[0]);
  your_emergency_manager.add(earliest_first[1]);
  your_emergency_manager.add(earliest_first[2]);
  SIMULATE_SIO("", your_emergency_manager.show_priority_emergency(953), {
    ASSERT_THAT(your_output, ContainsRegex(R"(0.h(r|our))"))
        << "Your program should show no difference in hours.";
    ASSERT_THAT(your_output, ContainsRegex(R"(31.min)"))
        << "Your program should show a 31 minute difference.";
  })
}

TEST_F(PriorityEmergency, HourDiffNoMinDiff1) {
  EmergencyManager your_emergency_manager;
  your_emergency_manager.add(earliest_first[0]);
  your_emergency_manager.add(earliest_first[1]);
  your_emergency_manager.add(earliest_first[2]);
  SIMULATE_SIO("", your_emergency_manager.show_priority_emergency(1022), {
    ASSERT_THAT(your_output, ContainsRegex(R"(1.h(r|our))"))
        << "Your program should show a 1 hour difference.";
    ASSERT_THAT(your_output, ContainsRegex(R"(0.min)"))
        << "Your program should show no difference in minutes.";
  })
}

TEST_F(PriorityEmergency, HourDiffNoMinDiff2) {
  EmergencyManager your_emergency_manager;
  your_emergency_manager.add(earliest_first[0]);
  your_emergency_manager.add(earliest_first[1]);
  your_emergency_manager.add(earliest_first[2]);
  SIMULATE_SIO("", your_emergency_manager.show_priority_emergency(1622), {
    ASSERT_THAT(your_output, ContainsRegex(R"(7.h(r|our))"))
        << "Your program should show a 7 hour difference.";
    ASSERT_THAT(your_output, ContainsRegex(R"(0.min)"))
        << "Your program should show no difference in minutes.";
  })
}

TEST_F(PriorityEmergency, HourDiffMinDiff) {
  EmergencyManager your_emergency_manager;
  your_emergency_manager.add(earliest_first[0]);
  your_emergency_manager.add(earliest_first[1]);
  your_emergency_manager.add(earliest_first[2]);
  SIMULATE_SIO("", your_emergency_manager.show_priority_emergency(1555), {
    ASSERT_THAT(your_output, ContainsRegex(R"(6.h(r|our))"))
        << "Your program should show a 6 hour difference.";
    ASSERT_THAT(your_output, ContainsRegex(R"(33.min)"))
        << "Your program should show 33 minute difference.";
  })
}

TEST_F(PriorityEmergency, CurrentTimeMinGreaterThanReportTimeMin) {
  EmergencyManager your_emergency_manager;
  your_emergency_manager.add(earliest_first[0]);
  your_emergency_manager.add(earliest_first[1]);
  your_emergency_manager.add(earliest_first[2]);
  SIMULATE_SIO("", your_emergency_manager.show_priority_emergency(1110), {
    ASSERT_THAT(your_output, ContainsRegex(R"(1.h(r|our))"))
        << "Your program should show a 1 hour difference.";
    ASSERT_THAT(your_output, ContainsRegex(R"(48.min)"))
        << "Your program should show a 48 minute difference.";
  })
}

TEST(GetFilename, Filename1) {
  std::string your_filename;
  SIMULATE_SIO(
      "emergencies.txt", { your_filename = get_filename(); },
      {
        ASSERT_THAT(your_filename, "emergencies.txt")
            << "The filename should be the string that the user input, "
               "emergencies.txt.";
      })
}

TEST(GetFilename, Filename2) {
  std::string your_filename;
  SIMULATE_SIO(
      "data.txt", { your_filename = get_filename(); },
      {
        ASSERT_THAT(your_filename, "data.txt")
            << "The filename should be the string that the user input, "
               "data.txt.";
      })
}

TEST_F(SaveFile, CreateFile) {
  EmergencyManager your_emergency_manager;
  your_emergency_manager.add(emergencies[0]);
  your_emergency_manager.add(emergencies[1]);
  your_emergency_manager.add(emergencies[2]);
  ASSERT_DURATION_LE(
      3, {SIMULATE_SIO(
             "", { your_emergency_manager.save_emergencies("save.txt"); }, {})})
  std::ifstream your_file;
  your_file.open("save.txt");
  ASSERT_TRUE(your_file.good())
      << "      The function should create a file using the filename provided "
         "by the user. In this case, save.txt.";
}

TEST_F(SaveFile, OneEmergency) {
  EmergencyManager your_emergency_manager;
  your_emergency_manager.add(emergencies[0]);
  ASSERT_DURATION_LE(
      3, {SIMULATE_SIO(
             "", { your_emergency_manager.save_emergencies("save.txt"); }, {})})

  std::ifstream your_file;
  your_file.open("save.txt");

  ASSERT_TRUE(your_file.good())
      << "      The function should create a file using the filename provided "
         "by the user. In this case, save.txt.";

  int your_file_size = 0;

  your_file >> your_file_size;
  your_file.ignore();

  ASSERT_EQ(your_file_size, 1) << "      The function should store 1 for the "
                                  "number of emergenices in the file.";

  std::string your_file_emergency_type;
  std::string your_file_description;
  std::string your_file_location;
  unsigned short int your_file_report_time;

  std::getline(your_file, your_file_emergency_type);

  ASSERT_EQ(your_file_emergency_type, "[Emergency]")
      << "      The function should save the emergency type, [Emergency]";

  std::getline(your_file, your_file_description);

  ASSERT_EQ(your_file_description, "Wildland Fire")
      << "      The function should save the description of the first "
         "emergency, Wildland Fire";

  std::getline(your_file, your_file_location);

  ASSERT_EQ(your_file_location, "Beaumont")
      << "      The function should save the location of the first emergency, "
         "Beaumont";

  your_file >> your_file_report_time;

  ASSERT_EQ(your_file_report_time, 922)
      << "      The function should save the report time of the first "
         "emergency, 922";

  your_file.close();
}

TEST_F(SaveFile, ThreeEmergencies) {
  EmergencyManager your_emergency_manager;
  your_emergency_manager.add(emergencies[0]);
  your_emergency_manager.add(emergencies[1]);
  your_emergency_manager.add(emergencies[2]);
  ASSERT_DURATION_LE(
      3, {SIMULATE_SIO(
             "", { your_emergency_manager.save_emergencies("save.txt"); }, {})})

  std::ifstream your_file;
  your_file.open("save.txt");

  ASSERT_TRUE(your_file.good())
      << "      The function should create a file using the filename provided "
         "by the user. In this case, save.txt.";

  int your_file_size = 0;

  your_file >> your_file_size;
  your_file.ignore();

  ASSERT_EQ(your_file_size, 3) << "      The function should store 3 for the "
                                  "number of emergencies in the file.";

  std::string your_file_emergency_type;
  std::string your_file_description;
  std::string your_file_other_emergencies;
  std::string your_file_location;
  unsigned short int your_file_report_time;

  // first route
  std::getline(your_file, your_file_emergency_type);

  ASSERT_EQ(your_file_emergency_type, "[Emergency]")
      << "      The function should save the emergency type, [Emergency]";

  std::getline(your_file, your_file_description);

  ASSERT_EQ(your_file_description, "Wildland Fire")
      << "      The function should save the name of the first emergency, "
         "Wildland Fire";

  std::getline(your_file, your_file_location);

  ASSERT_EQ(your_file_location, "Beaumont")
      << "      The function should save the location of the first emergency, "
         "Beaumont";

  your_file >> your_file_report_time;
  your_file.ignore();

  ASSERT_EQ(your_file_report_time, 922)
      << "      The function should save the report time of the first "
         "emergency, 922";

  // second route

  std::getline(your_file, your_file_emergency_type);

  ASSERT_EQ(your_file_emergency_type, "[MultipleEmergency]")
      << "      The function should save the emergency type, "
         "[MultipleEmergency]";

  std::getline(your_file, your_file_description);

  ASSERT_EQ(your_file_description, "Camp Fire")
      << "      The function should save the description of the second "
         "emergency, Camp Fire";

  std::getline(your_file, your_file_other_emergencies);

  ASSERT_EQ(your_file_other_emergencies, "Missing person")
      << "      The function should save the other emergencies of the second "
         "emergency, Missing person";

  std::getline(your_file, your_file_location);

  ASSERT_EQ(your_file_location, "Butte County")
      << "      The function should save the location of the second emergency, "
         "Butte County";

  your_file >> your_file_report_time;
  your_file.ignore();

  ASSERT_EQ(your_file_report_time, 945)
      << "      The function should save the report time of the second "
         "emergency, 945";

  // third route
  std::getline(your_file, your_file_emergency_type);

  ASSERT_EQ(your_file_emergency_type, "[Emergency]")
      << "      The function should save the emergency type, [Emergency]";

  std::getline(your_file, your_file_description);

  ASSERT_EQ(your_file_description, "Vegetation Fire")
      << "      The function should save the description of the third "
         "emergency, Vegetation Fire";

  std::getline(your_file, your_file_location);

  ASSERT_EQ(your_file_location, "Aguanga")
      << "      The function should save the location of the third emergency, "
         "Aguanga";

  your_file >> your_file_report_time;

  ASSERT_EQ(your_file_report_time, 1602)
      << "      The function should save the report time of the third "
         "emergency, 1602";

  your_file.close();
}

///
TEST(LoadFile_, NoFile) {
  EmergencyManager your_emergency_manager;

  SIMULATE_SIO(
      "", { your_emergency_manager.load_emergencies("nonexistentfile.txt"); },
      {
        ASSERT_THAT(your_output, HasSubstr("does not exist"))
            << "      The function should show an error if the file to be "
               "loaded does not exist.";
      })
}

TEST_F(LoadFile, OneEmergency) {
  std::ofstream your_file;
  your_file.open("load.txt");
  your_file << "1\n[Emergency]\nWildland Fire\nBeaumont\n922";
  your_file.close();

  EmergencyManager your_emergency_manager;

  SIMULATE_SIO(
      "",
      {
        ASSERT_DURATION_LE(
            3, { your_emergency_manager.load_emergencies("load.txt"); })
        your_emergency_manager.display_emergencies();
      },
      {
        ASSERT_THAT(your_output, HasSubstr("Wildland Fire"))
            << "      The function should load the description of the first "
               "emergency, Wildland Fire.";
        ASSERT_THAT(your_output, HasSubstr("Beaumont"))
            << "      The function should load the location of the first "
               "emergency, Beaumont.";
        ASSERT_THAT(your_output, HasSubstr("922"))
            << "      The function should load the report time of the first "
               "emergency, 922.";
      })
}

TEST_F(LoadFile, ThreeEmergencies) {
  std::ofstream your_file;
  your_file.open("load.txt");
  your_file << "3\n[Emergency]\nWildland "
               "Fire\nBeaumont\n922\n[MultipleEmergency]\nCamp Fire\nMissing "
               "person\nButte County\n945\n[PotentialEmergency]\nFlood\nTonto "
               "Basin\n2000\n1327\n";
  your_file.close();

  EmergencyManager your_emergency_manager;

  SIMULATE_SIO(
      "",
      {
        ASSERT_DURATION_LE(
            3, { your_emergency_manager.load_emergencies("load.txt"); })
        your_emergency_manager.display_emergencies();
      },
      {
        ASSERT_THAT(your_output, HasSubstr("Wildland Fire"))
            << "      The function should load the description of the first "
               "emergency, Wildland Fire.";
        ASSERT_THAT(your_output, HasSubstr("Beaumont"))
            << "      The function should load the location of the first "
               "emergency, Beaumont.";
        ASSERT_THAT(your_output, HasSubstr("922"))
            << "      The function should load the report time of the first "
               "emergency, 922.";
        // second route
        ASSERT_THAT(your_output, HasSubstr("Camp Fire"))
            << "      The function should load the description of the second "
               "emergency, Camp Fire.";
        ASSERT_THAT(your_output, HasSubstr("Missing person"))
            << "      The function should load the other emergencies of the "
               "second emergency, Missing person.";
        ASSERT_THAT(your_output, HasSubstr("Butte County"))
            << "      The function should load the location of the second "
               "emergency, Little Lake.";
        ASSERT_THAT(your_output, HasSubstr("945"))
            << "      The function should load the report time of the second "
               "emergency, 2049.";
        // third route
        ASSERT_THAT(your_output, HasSubstr("Flood"))
            << "      The function should load the description of the third "
               "emergency, Fllood.";
        ASSERT_THAT(your_output, HasSubstr("Tonto Basin"))
            << "      The function should load the location of the third "
               "emergency, Tonto Basin.";
        ASSERT_THAT(your_output, HasSubstr("2000"))
            << "      The function should load the estimated time of the third "
               "emergency, 2000.";
        ASSERT_THAT(your_output, HasSubstr("1327"))
            << "      The function should load the report time of the third "
               "emergency, 1327.";
      })
}

TEST(Input, CreateExit) {
  std::string user_input = "E\nWildland Fire\nBeaumont\n922\nX\n";
  ASSERT_EXECEXIT("tuffyaid", user_input, 3);
}

TEST(Input, DisplayExit) {
  std::string user_input = "D\nX\n";
  ASSERT_EXECEXIT("tuffyaid", user_input, 3);
}

TEST(Input, CreateMultipleDisplayExit) {
  std::string user_input =
      "M\nCamp Fire\nMissing Person\nButte County\n945\nD\nX\n";
  ASSERT_EXECEXIT("tuffyaid", user_input, 3);
}

TEST(Input, DisplayCreateMultipleExit) {
  std::string user_input =
      "D\nM\nCamp Fire\nMissing Person\nButte County\n945\nX\n";
  ASSERT_EXECEXIT("tuffyaid", user_input, 3);
}

TEST(Input, CreateShowPriorityExit) {
  std::string user_input = "E\nWildland Fire\nBeaumont\n922\nP\n1100\nX\n";
  ASSERT_EXECEXIT("tuffyaid", user_input, 3);
}

TEST(Input, ShowPriorityCreateExit) {
  std::string user_input =
      "P\n1100\nM\nCamp Fire\nMissing Person\nButte County\n945\nX\n";
  ASSERT_EXECEXIT("tuffyaid", user_input, 3);
}

TEST(Input, DisplayShowPriorityExit) {
  std::string user_input = "D\nP\n1100\nX\n";
  ASSERT_EXECEXIT("tuffyaid", user_input, 3);
}

TEST(Input, ShowPriorityDisplayExit) {
  std::string user_input = "P\n1100\nD\nX\n";
  ASSERT_EXECEXIT("tuffyaid", user_input, 3);
}

TEST(Input, CreateDisplayCreateMultipleDisplayExit) {
  std::string user_input = "E\nWildland Fire\nBeaumont\n922\nD\nM\nCamp "
                           "Fire\nMissing Person\nButte County\n945\nD\nX\n";
  ASSERT_EXECEXIT("tuffyaid", user_input, 3);
}

///
TEST_F(DriverSaveFile, SaveExit) {
  std::string user_input = "S\nsave.txt\nX\n";
  ASSERT_EXECEXIT("tuffyaid", user_input, 3);
}

TEST_F(DriverSaveFile, DisplaySaveExit) {
  std::string user_input = "D\nS\nsave.txt\nX\n";
  ASSERT_EXECEXIT("tuffyaid", user_input, 3);
}

TEST_F(DriverSaveFile, SaveDisplayExit) {
  std::string user_input = "S\nsave.txt\nD\nX\n";
  ASSERT_EXECEXIT("tuffyaid", user_input, 3);
}

TEST_F(DriverSaveFile, SaveCreateExit) {
  std::string user_input = "S\nsave.txt\nE\nWildland Fire\nBeaumont\n922\nX\n";
  ASSERT_EXECEXIT("tuffyaid", user_input, 3);
}

TEST_F(DriverSaveFile, CreateMultipleSaveExit) {
  std::string user_input =
      "M\nCamp Fire\nMissing Person\nButte County\n945\nS\nsave.txt\nX\n";
  ASSERT_EXECEXIT("tuffyaid", user_input, 3);
}

TEST_F(DriverSaveFile, ShowPrioritySaveExit) {
  std::string user_input = "P\n1100\nS\nsave.txt\nX\n";
  ASSERT_EXECEXIT("tuffyaid", user_input, 3);
}

TEST_F(DriverSaveFile, SaveShowPriorityExit) {
  std::string user_input = "S\nsave.txt\nP\n1100\nX\n";
  ASSERT_EXECEXIT("tuffyaid", user_input, 3);
}

TEST_F(DriverSaveFile, SaveLoadExit) {
  std::string user_input = "S\nsave.txt\nL\nsave.txt\nX\n";
  ASSERT_EXECEXIT("tuffyaid", user_input, 3);
}

TEST_F(DriverSaveFile, LoadSaveExit) {
  std::string user_input = "L\nsave.txt\nS\nsave.txt\nX\n";
  ASSERT_EXECEXIT("tuffyaid", user_input, 3);
}

TEST_F(DriverLoadFile, LoadExit) {
  std::string user_input = "L\nload.txt\nX\n";
  ASSERT_EXECEXIT("tuffyaid", user_input, 3);
}

TEST_F(DriverLoadFile, DisplayLoadExit) {
  std::string user_input = "D\nL\nload.txt\nX\n";
  ASSERT_EXECEXIT("tuffyaid", user_input, 3);
}

TEST_F(DriverLoadFile, LoadDisplayExit) {
  std::string user_input = "L\nload.txt\nD\nX\n";
  ASSERT_EXECEXIT("tuffyaid", user_input, 3);
}

TEST_F(DriverLoadFile, LoadCreateExit) {
  std::string user_input = "L\nload.txt\nE\nWildland Fire\nBeaumont\n922\nX\n";
  ASSERT_EXECEXIT("tuffyaid", user_input, 3);
}

TEST_F(DriverLoadFile, CreateLoadExit) {
  std::string user_input = "E\nWildland Fire\nBeaumont\n922\nL\nload.txt\nX\n";
  ASSERT_EXECEXIT("tuffyaid", user_input, 3);
}

TEST_F(DriverLoadFile, ShowPriorityLoadExit) {
  std::string user_input = "P\n1100\nL\nload.txt\nX\n";
  ASSERT_EXECEXIT("tuffyaid", user_input, 3);
}

TEST_F(DriverLoadFile, LoadShowPriorityExit) {
  std::string user_input = "L\nload.txt\nP\n1100\nX\n";
  ASSERT_EXECEXIT("tuffyaid", user_input, 3);
}

///
TEST(Driver, CreateDisplayExit) {
  std::string user_input = "E\nWildland Fire\nBeaumont\n922\nD\nX\n";
  ASSERT_EXECTHAT("tuffyaid", user_input, HasSubstr("Wildland Fire"))
      << "Your program should show the created emergency's description "
         "Wildland Fire.";
  ASSERT_EXECTHAT("tuffyaid", user_input, HasSubstr("Beaumont"))
      << "Your program should show the created emergency's location, Beaumont.";
  ASSERT_EXECTHAT("tuffyaid", user_input, HasSubstr("922"))
      << "Your program should show the created emergency's report time 922.";
}

TEST(Driver, CreateCreatePotentialDisplayExit) {
  std::string user_input = "E\nWildland Fire\nBeaumont\n922\nO\nFlood\nTonto "
                           "Basin\n2000\n1327\nD\nX\n";
  ASSERT_EXECTHAT("tuffyaid", user_input, HasSubstr("Wildland Fire"))
      << "Your program should show the first emergency's description Wildland "
         "Fire.";
  ASSERT_EXECTHAT("tuffyaid", user_input, HasSubstr("Beaumont"))
      << "Your program should show the first emergency's location, nBeaumont.";
  ASSERT_EXECTHAT("tuffyaid", user_input, HasSubstr("922"))
      << "Your program should show the first emergency's report time 922.";

  ASSERT_EXECTHAT("tuffyaid", user_input, HasSubstr("Flood"))
      << "Your program should show the second emergency's description, Flood.";
  ASSERT_EXECTHAT("tuffyaid", user_input, HasSubstr("Tonto Basin"))
      << "Your program should show the second emergency's location, Tonto "
         "Basin";
  ASSERT_EXECTHAT("tuffyaid", user_input, HasSubstr("2000"))
      << "Your program should show the second emergency's estimated time, "
         "2000.";
  ASSERT_EXECTHAT("tuffyaid", user_input, HasSubstr("1327"))
      << "Your program should show the second emergency's report time, 1327.";
}

TEST(Driver, CreateCreateMultipleDisplayExit) {
  std::string user_input = "E\nWildland Fire\nBeaumont\n922\nM\nCamp "
                           "Fire\nMissing Person\nButte County\n945\nD\nX\n";
  ASSERT_EXECTHAT("tuffyaid", user_input, HasSubstr("Wildland Fire"))
      << "Your program should show the first emergency's description Wildland "
         "Fire.";
  ASSERT_EXECTHAT("tuffyaid", user_input, HasSubstr("Beaumont"))
      << "Your program should show the first emergency's location, nBeaumont.";
  ASSERT_EXECTHAT("tuffyaid", user_input, HasSubstr("922"))
      << "Your program should show the first emergency's report time 922.";
  ASSERT_EXECTHAT("tuffyaid", user_input, HasSubstr("Camp Fire"))
      << "Your program should show the second emergency's description Camp "
         "Fire.";
  ASSERT_EXECTHAT("tuffyaid", user_input, HasSubstr("Missing Person"))
      << "Your program should show the second emergency's other emergencies "
         "Missing person.";
  ASSERT_EXECTHAT("tuffyaid", user_input, HasSubstr("Butte County"))
      << "Your program should show the second emergency's location, Butte "
         "County.";
  ASSERT_EXECTHAT("tuffyaid", user_input, HasSubstr("945"))
      << "Your program should show the second emergency's report time 945.";
}

TEST(Driver, CreateCreateShowPriorityExit) {
  std::string user_input =
      "E\nWildland Fire\nBeaumont\n922\nM\nCamp Fire\nMissing Person\nButte "
      "County\n945\nP\n1100\nX\n";
  ASSERT_EXECTHAT("tuffyaid", user_input, HasSubstr("Wildland Fire"))
      << "Your program should show the priority emergency's description "
         "Wildland Fire.";
  ASSERT_EXECTHAT("tuffyaid", user_input, HasSubstr("Beaumont"))
      << "Your program should show the priority emergency's location, "
         "nBeaumont.";
  ASSERT_EXECTHAT("tuffyaid", user_input, HasSubstr("922"))
      << "Your program should show the priority emergency's report time 922.";
  ASSERT_EXECTHAT("tuffyaid", user_input, ContainsRegex(R"(1.h(r|our))"))
      << "Your program should show that the hour difference between the "
         "priority emergency and current time is 1 hours.";
  ASSERT_EXECTHAT("tuffyaid", user_input, ContainsRegex(R"(38.min)"))
      << "Your program should show that the minute difference between the "
         "priority emergency and current time is 38 minutes .";
}

TEST_F(DriverSaveFile, CreateCreateMultipleSaveExit) {
  ASSERT_DURATION_LE(3, {
    std::string user_input =
        "E\nWildland Fire\nBeaumont\n922\nM\nCamp Fire\nMissing person\nButte "
        "County\n945\nS\nsave.txt\nX\n";
    exec_program("tuffyaid", user_input);
  })

  std::ifstream your_file;
  your_file.open("save.txt");

  ASSERT_TRUE(your_file.good())
      << "      The program should create a file using the filename provided "
         "by the user. In this case, save.txt.";

  int your_file_size = 0;

  your_file >> your_file_size;
  your_file.ignore();

  ASSERT_EQ(your_file_size, 2) << "      The program should store 2 for the "
                                  "number of emergencies in the file.";

  std::string your_file_emergency_type;
  std::string your_file_description;
  std::string your_file_other_emergencies;
  std::string your_file_location;
  unsigned short int your_file_report_time;

  // first route
  std::getline(your_file, your_file_emergency_type);

  ASSERT_EQ(your_file_emergency_type, "[Emergency]")
      << "      The function should save the emergency type, [Emergency]";

  std::getline(your_file, your_file_description);

  ASSERT_EQ(your_file_description, "Wildland Fire")
      << "      The program should save the description of the first "
         "emergency, Wildland Fire";

  std::getline(your_file, your_file_location);

  ASSERT_EQ(your_file_location, "Beaumont")
      << "      The program should save the location of the first emergency, "
         "Beaumont";

  your_file >> your_file_report_time;
  your_file.ignore();

  ASSERT_EQ(your_file_report_time, 922)
      << "      The program should save the report time of the first "
         "emergency, 922";

  // second route

  std::getline(your_file, your_file_emergency_type);

  ASSERT_EQ(your_file_emergency_type, "[MultipleEmergency]")
      << "      The function should save the emergency type, "
         "[MultipleEmergency]";

  std::getline(your_file, your_file_description);

  ASSERT_EQ(your_file_description, "Camp Fire")
      << "      The program should save the description of the second "
         "emergency, Camp Fire";

  std::getline(your_file, your_file_other_emergencies);

  ASSERT_EQ(your_file_other_emergencies, "Missing person")
      << "      The program should save the other emergencies of the second "
         "emergency, Missing person";

  std::getline(your_file, your_file_location);

  ASSERT_EQ(your_file_location, "Butte County")
      << "      The program should save the location of the second emergency, "
         "Butte County";

  your_file >> your_file_report_time;
  your_file.ignore();

  ASSERT_EQ(your_file_report_time, 945)
      << "      The program should save the report time of the second "
         "emergency, 945";

  your_file.close();
}

TEST_F(DriverLoadFile, LoadDisplayExitOutput) {
  ASSERT_DURATION_LE(3, {
    std::string user_input = "L\nload.txt\nD\nX\n";
    ASSERT_EXECTHAT("tuffyaid", user_input, HasSubstr("Wildland Fire"))
        << "Your program should show the first emergency's description "
           "Wildland Fire.";
    ASSERT_EXECTHAT("tuffyaid", user_input, HasSubstr("Beaumont"))
        << "Your program should show the first emergency's location, Beaumont.";
    ASSERT_EXECTHAT("tuffyaid", user_input, HasSubstr("922"))
        << "Your program should show the first emergency's report time 922.";
    ASSERT_EXECTHAT("tuffyaid", user_input, HasSubstr("Camp Fire"))
        << "Your program should show the second emergency's description Camp "
           "Fire.";
    ASSERT_EXECTHAT("tuffyaid", user_input, HasSubstr("Missing person"))
        << "Your program should show the second emergency's other emergencies "
           "Missing person.";
    ASSERT_EXECTHAT("tuffyaid", user_input, HasSubstr("Butte County"))
        << "Your program should show the second emergency's location, Butte "
           "County.";
    ASSERT_EXECTHAT("tuffyaid", user_input, HasSubstr("945"))
        << "Your program should show the second emergency's report time 945.";
    ASSERT_EXECTHAT("tuffyaid", user_input, HasSubstr("Vegetation Fire"))
        << "Your program should show the third emergency's description "
           "Vegetation Fire.";
    ASSERT_EXECTHAT("tuffyaid", user_input, HasSubstr("Aguanga"))
        << "Your program should show the third emergency's location, Aguanga.";
    ASSERT_EXECTHAT("tuffyaid", user_input, HasSubstr("1602"))
        << "Your program should show the third emergency's report time 1602.";
  })
}

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  ::testing::UnitTest::GetInstance()->listeners().Append(new SkipListener());
  return RUN_ALL_TESTS();
}
