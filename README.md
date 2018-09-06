# Overview
An algorithmic trading application being written in C++ for small portfolios.
Is being built to work with the Tradier brokerage API.

# Dependencies
Relies on the libcurl C networking library.
Install the library and compile with the -lcurl linker flag.
Refer to: https://github.com/curl/curl.

# Building
The application can be compiled by running the myAlgo/build.bash script.

# GitHub Crash Course
To contribute towards an issue, first clone the repository (git clone https://github.com/joshuakarbi/algorithmic_trader.git), and then follow these steps:
  
  1. Assign the issue to yourself.
  2. Make a branch off of master following the format trader-ISSUE_NUMBER (ie. trader-2).
  3. Do a git fetch and git pull on your local copy (git fetch && git pull).
  4. Checkout your new branch (git checkout BRANCH_NAME)
  5. Write and test your new code.
  6. Commit your code to git (git commit -a OR git add CHANGED_FILE && git commit).
  7. Push your code to your remote branch (git push BRANCH_NAME).
  8. Create a pull request to merge BRANCH_NAME into master.
  
Note that some development environments can do all of this for you through their GUI.
