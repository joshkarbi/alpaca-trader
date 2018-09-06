# Overview
An algorithmic trading application being written in C++ for small portfolios.
Is being built to work with brokerage API's that use https GET requests (ie. Tradier).

# Contributions are Welcome!
Please contribute by forking and creating pull requests.

# Dependencies
Relies on libcurl C networking library.

# Compiling
Required -lcurl linker flag, and having the curl library installed in your include directory.
Refer to: https://github.com/curl/curl.

# GitHub Crash Course
To contribute towards an issue, first clone the repository (git clone https://github.com/joshuakarbi/algorithmic_trader.git), and then follow these steps:
  
  1. Assign the issue to yourself.
  2. Make a branch off of master following the format trader-ISSUE_NUMBER (ie. trader-2).
  3. Do a git fetch and git pull on your local copy (git fetch && git pull).
  4. Checkout your new branch (git checkout <branch name>)
  5. Write and test your new code.
  6. Commit your code to git (git commit -a OR git add <changed file> && git commit).
  7. Push your code to your remote branch (git push <branch name>).
  8. Create a pull request to merge <branch name> into master.
  
Note that some development environments can do all of this for you through their GUI.
