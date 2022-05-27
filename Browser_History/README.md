Browser History
CPSC 131 Spring 2020
 
Introduction
Modern web browsers keep track of browsing history which allows users to recall previously visited web pages using the back and forward arrow buttons. When a user navigates back to a previous web page, they also have the option to navigate forward in the navigation history using the forward arrow button. However, if the user navigates back to a previous page and then visits a new web page, all web pages that previously could be accessed with the forward arrow button are discarded. This behavior is well suited for Linked Lists . In this project you will write C++ code to model this behavior.
Objective
The public interface of the class (BrowserHistory) should keep track of the current webpage. The current webpage will change when the user clicks the back or forward buttons or when the user visits a new webpage:
●	void BrowserHistory::backButton(): current webpage changes to the previous one in the visit sequence. If there is no previous page, current web page stays the same.
●	void BrowserHistory::forwardButton(): current webpage changes to the next one in the visit sequence. If there is no such page, current web page stays the same.
●	void BrowserHistory::visitSite(string url, size_t filesize): user visits a webpage with the given URL and web page size (in number of bytes).

BrowserHistory should return the current webpage’s url and pagesize via these methods:
●	string BrowserHistory::currentUrl(). Returns the current url. If there is no webpage in the history, the function returns the empty string.
●	size_t BrowserHistory::currentPageSize(). Returns the current webpage’s page size. If there is no webpage in the history, the function returns 0.
●	size_t BrowserHistory::getHistoryLength() returns the length of the webpage history.

The logic of these operations is shown in the example below. Each box indicates a webpage (URL, page size). The green arrow indicates the current webpage.
 


BrowserHistory should also be able to read a simple text file of a user’s browsing history containing their actions. Each line in the text file begins with one of three action words: visit, back, and forward. Back and forward will simulate the user pressing the back and forward arrow buttons of their browser. If the action is visit, it will be followed with a web URL (string) and the page size (positive integer). Update the current webpage based on this text file in method:
●	void BrowserHistory::readFile(string filename)
