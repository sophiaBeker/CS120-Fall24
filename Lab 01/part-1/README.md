![Lab Tests](../../../actions/workflows/cc-lab-passing.yml/badge.svg)

# Linux, BASH Shell, and Github

The purpose of this lab is to get familiar with the Linux system, the BASH shell, and GitHub. As part of the
lab, you will get to compile and run a [hello world program](https://en.wikipedia.org/wiki/%22Hello,_World!%22_program).

This assignment is to be completed by pairs of students using the [_pair programming_](https://en.wikipedia.org/wiki/Pair_programming) software development technique. This is where one student is the _driver_ and types whatever the other student says. The other student is known as the _navigator_. 

Students should switch roles every 15 minutes or whenever directed by the instructor. In this lab, you are recommended to take turns using the same computer.

You will need a computer that runs Linux and a GitHub account.

Only one repository per pair of students shall be submitted. Please do not submit multiple repositories since this may cause confusion and incorrect grades. Following the instructions given to create a GitHub team for this lab assignment.

A lab assignment is submitted when it is _pushed_ to GitHub. The instructions below walk you through the process. You may push to GitHub as many times as you want.

All lab computers have Linux available. Instructions on how to start-up (boot) a lab computer into Linux is posted on the course Canvas page.

In case your lab computer does not work or you do not have your own Linux laptop, consult with your instructor about what to do.

Do not leave the laboratory until you have completed the lab. If you complete the lab early, demonstrate your lab to your instructor and ask for permission to leave early.

## Background

### UNIX system

Before there was Linux there was UNIX.

You might be familiar with operating systems like Windows or macOS. UNIX is another operating system that was developed back in 1969 by AT&T Bell labs. Operating systems manage the computer resources such as the memory, hard-drives, keyboard, mouse, screen, etc. For example, whenever you are copying a photo from your camera SD card connected to your computer to the computer's hard-drive, the operating system is taking care of performing this action in the background.

Many operating systems have been developed as an extension, or very similar to the UNIX operating system. Some of these are Linux or macOS.

#### The UNIX Shell

There are many ways to interact with an operating system: you can see the visual screen of your phone and interact with it by touching it, or you can listen to a Google Home device and interact with it by talking to it. One of the most basic ways to interact with an operating system is by using the UNIX shell, which looks like this:

```bash
$
```

Maybe your shell prompt does not look exactly like the example given. The important part is that there is always a `$` (dollar sign) symbol. This is what is called a prompt. The prompt is where you enter commands for the shell to execute.

The UNIX shell is a program that expects the user (you) to input commands (using a keyboard in most cases) and then sends your commands to the operating system to be executed on your behalf. There are multiple types of UNIX shells which determine the format/style of commands it expects. In this class, we will be using the *Bash* UNIX shell.

In the remainder of this document, the prompt shall be represented by just the `$` character. When you want to type commands into your shell on your computer, remember to only type the command - not the `$`.

*Note: you might notice that whenever you type your password in the shell, nothing will show up. This is working as intended (security feature). The terminal does let you type your password whenever it is asked, but it does not show any hidden characters as you type it.*

### Git, GitHub & GitHub Classroom

When writing code for a program, it is extremely helpful to keep track of the changes that you have made to your code. Sometimes you realize that a piece of code you recently wrote is actually broken and you need to revert it to an older version. A software that allows you to keep track of your code changes is called a version control system.

In addition, when working in a project with multiple people, programmers might need to update the same file at the same time. A **distributed** version control system allows each member of a team to download a copy of the existing code so that they can work on it locally, and later integrate it with the code from other members of the team. This allows the team to implement a software faster.

Git is a free and open source distributed version control system and is widely used in academia as well as the industry. GitHub is a web-based service that provides an online server to host code online that can be updated using Git. You can think of GitHub the same way you think of Dropbox, but made specifically to integrate with the Git system.

GitHub Classroom is a service that GitHub offers specifically designed for implementing Git in a classroom environment, where students download some code, implement their assignments, and then submit the code through Git, allowing the instructor to see all the submissions. We will be using GitHub classroom in all of the coding assignments of this class (labs and projects).

Git is a extremely powerful tool that allows teams to work on multiple versions of code, and because of this, Git can also get very complicated. For the purposes of this course, we will be learning three basic Git operations that will allow you to submit your assignments:

1. `git clone`, which allows you to download a copy of the code stored in GitHub onto your local computer so that you can edit it locally.
1. `git commit`, which is used to store (or save) a current version of your code (think of it as clicking the save button on a document you are editing).
1. `git push`, which uploads all of the versions you have stored each time you execute `git commit`. You can *commit* your code multiple times, creating multiple versions of your code. For these assignments, we will always only grade the most recent *commit* of your code (which is the most recent version).

For this assignment, you must have a GitHub account linked to your university email.

If you have never had a GitHub account, you can create one by visiting the [GitHub](https://github.com/) website and filling up the form to sign up for GitHub. Make sure to use your university email when creating the account. Make sure you verify your email (you will get a verification email after creating your account).

If you already have a GitHub account, but it was created using a different email, you need to link your GitHub account to your university email. Log into your account on the GitHub website and then visit the [Email settings](https://github.com/settings/emails) page to add your university email. Once you add your university email, you will receive an email which will allow you to verify that the email belongs to you.

## Lab instructions

### Configuring Git

The `git` command communicates with the online service GitHub. Although you login to GitHub, `git` is a command line tool that does not know who you are. We must configure `git` to know your name and email address.

It is important that you have your CSUF email address as one of your email addresses in your GitHub account. If you have not added your CSUF email address already, please do so before continuing. Instructions are online on how to add an [email address to your GitHub account](https://docs.github.com/en/account-and-profile/setting-up-and-managing-your-github-user-account/managing-email-preferences/adding-an-email-address-to-your-github-account).

#### Authentication

GitHub has changed the way authentication works as of August 13, 2021. The videos that your instructor has shared and many other tutorials use the http authentication method which is no longer supported. GitHub only works with Personal Access Tokens or [SSH](https://en.wikipedia.org/wiki/Secure_Shell) keys.

Your instructor recommends using _Personal Access Tokens_ unless you have an existing SSH keychain. If you do not know if you have a SSH keychain, then you do not have a SSH keychain; use Personal Access Tokens.

GitHub has a [step-by-step tutorial how to create a Personal Access Token (classic)](https://docs.github.com/en/authentication/keeping-your-account-and-data-secure/creating-a-personal-access-token#creating-a-personal-access-token-classic). (Use _Classic Personal Access Tokens_.) Follow the steps **carefully** to create your own Personal Authentication Token or PAT. Please give your PAT a descriptive name such as "CPSC Spring 2043" and set an expiration date that is at the end of the semester. (In Fall, set the date to a day in January of the following year and, in Spring, set the date to June of the same year.)

**Important: make sure the box for "repo" is checked.** You can check all of the other boxes if you want but you must check the "repo" box which will also check "repo:staus", "repo_deployment", "public_repo". A common error is to forget to check this box which will mean your PAT will not work.

Once you click "Generate token", a PAT will be displayed on the page. Copy and paste the PAT somewhere safe. You will need to refer to the PAT a few more times and GitHub will never show you the PAT again. If you forget to copy and paste the PAT or loose it, you must create a new PAT.

The PAT is a long alphanumeric string which will be used in place of your GitHub password when you authenticate with GitHub via the git command line utility. Handle it carefully, like you would handle any other secret password.

#### Save Your Configuration

In order to use git on a computer, you need to configure the git program to know who you are and how to authenticate with GitHub.

To simplify the process, your instructor has provided a script which you can use to automate saving your configuration. When you have a Linux computer ready to use with git, run this command. The command will ask you a series of questions. Answer the questions and it will create your git configuration. Remember to use your @csu.fullerton.edu email address. If you make a mistake, run the script again.

You must do this configuration only once per computer. If you complete this process on your personal laptop, you only need to do it once. If you complete this process on a computer in a public laboratory, then you must do it every time you use a laboratory computer.

```
wget -q https://raw.githubusercontent.com/mshafae/tusk/main/gcf.sh && sh ./gcf.sh
```

The command above downloads a file named gcf.sh and runs it on your computer. Once you have git configured, you can delete or ignore the gcf.sh file.

The script will build a plugin that will be used to save your PAT so you only have to type it in once the first time you use it. After that, your computer will remember your PAT and type it in for you.

If you run the above command, you should expect to see output that is similar (not identical) to the example below.

```
$ wget -q https://raw.githubusercontent.com/mshafae/tusk/main/gcf.sh && sh ./gcf.sh
We are going to edit the file /home/tuffytitan/.gitconfig to make git work better for you.
Ready, set, go!
What is your full name? Please include your first and last name. Tuffy Titan
You entered "Tuffy Titan"
Is this correct? [y/n] y
Great, here's another question...
What's your CSUF email address? tuffytitan@csu.fullerton.edu
You entered "tuffytitan@csu.fullerton.edu"
Is this correct? [y/n] y
Excellent, here's another question...

We're about to install some software and compile a few things.
This may take a minute.

If you are prompted for a password, type in the password
you used to login to this computer. Remember, it won't
print out what you type as a security precaution.
[sudo] password for tuffytitan: 
Fetched 11.6 MB in 3s (3,452 kB/s)                                       
Reading package lists... Done
Updated your packages, let's install some packages...
Reading package lists... Done
Building dependency tree       
Reading state information... Done
seahorse is already the newest version (3.36-1).
libsecret-1-0 is already the newest version (0.20.4-0ubuntu1).
libsecret-1-dev is already the newest version (0.20.4-0ubuntu1).
0 upgraded, 0 newly installed, 0 to remove and 82 not upgraded.
Great, the packages were installed. Let's build libsecret...
make: Entering directory '/usr/share/doc/git/contrib/credential/libsecret'
make: Nothing to be done for 'all'.
make: Leaving directory '/usr/share/doc/git/contrib/credential/libsecret'
Excellent, we've got all the parts ready to go.
Let's write out a new git configuration.

You're all set! Try using git to push or clone and see if your credentials are saved.
If you need to add or remove your GitHub password use the program named 'Passwords and Keys' and click 'Login', look for https://@github.com. Right click on it and you can edit the your saved GitHub password.
$ 
```

Once you have a PAT and you have configured your git utility, the next time you attempt to clone (via https) a repository from GitHub, use your GitHub username and your PAT to authenticate. The PAT will be cached (saved) to your account and you will not have to type it in again. You'll know it is working 100% correctly when you can clone, push, and pull from GitHub without being prompted for your username and password.

If you run into trouble or are confused, ask for help from your instructor.

### Cloning the Git Repository

Before moving on, make sure you have created and saved your GitHub PAT. Without the PAT, you will not be able to save your changes back to GitHub.

Next, make sure you are logged into GitHub by visiting https://github.com and verifying you are logged in. (If you are logged in, you will see an icon in the upper right hand corner of your web browser which represents your account's profile. If you are not logged in, the page will have a signup link instead of your profile.)

Once you are logged into your GitHub account, open the assignment URL (link) that your instructor has shared with you. It looks like this: https://classroom.github.com/a/some_random_code.

After opening that link, GitHub will generate the your own repository that will contain the starter code of the lab. This is the same repository where you will be pushing (submitting) your lab for grading. Once the repository is generated, a similar message will show:

> Your assignment has been created here: https://github.com/some-github-organization/cpsc-120-lab-01-your_github_team_name

Open the link to see the web-view of your GitHub repository. In there you will see one file and one directory:

1. `AUTHORS.md`: a document identifying who are the authors of the lab (initially blank and filled in by the student pair).
1. `README.md`: a document introducing the structure and rubric of the lab.
1. `part-1`: the directory with the starter code for your lab assignment.

Inside of the `part-1` directory:

1. `README.md`: an exact copy of the file you are reading right now.
1. `hello.cc`: the starter code for your lab assignment.

Now we need to clone your repository into your local computer so that you can start working with that code. To keep your files organized, we will first create a folder for this class, and in that folder we will clone your repository.

#### Creating a folder

By default, opening a terminal will take you straight to your home directory, which is usually referred as `~` (tilde). If you are using Linux, the location of your home directory is `/home/your_user_name` (you can check by running the `pwd` command).

Let's go ahead and create a folder in your home directory called `cpsc120` by running the following command:

```
$ mkdir cpsc120
```

After you press enter, the folder cpsc120 will be created, which you can verify by listing all the files and folder under your home directory:

```
$ ls
cpsc120 Desktop Documents ...
```

#### Accessing the folder (changing a directory)

Now, let's enter the folder so that you can clone your repository inside. We are going to use the `cd` command, which stands for *change directory*:

```
$ cd cpsc120
$
```

#### Cloning the git repository

Now we are ready to clone your repository. Go back to the web-view of your GitHub repository and click on the **Clone or download** green button on the top right, and then click on the copy button right next to the repository address. Then, go back to the terminal and run the following command:

```
$ git clone <paste repository URL>
```

The command will ask you to input your GitHub username and password. **Use your PAT as your password.** Once you enter that information, the repository is then downloaded (cloned) into your computer. The whole process will look similar to this:

```bash
$ git clone https://github.com/some-github-organization/cpsc-120-lab-01-your_github_team_name.git
Username for 'https://github.com': your_user_name
Password for 'https://github.con':
Cloning into 'cpsc-120-lab-01-your_user_name'...
remote: Counting objects: 9, done.
remote: Compressing objects: 100% (6/6), done.
remote: Total 9 (delta 1), reused 9 (delta 1), pack-reused 0
Unpacking objects: 100% (9/9), done.
```

**When you type in your password, the computer will not show what you type.** It will look as though you are not typing anything at all. This is a security precaution to make sure no one can see your password. Remember to type slowly and carefully so you do not make any typographical errors. Remeber to use your PAT as your password.

Once the command completes, you can notice that there is a new folder called `cpsc-120-lab-01-your_github_team_name`:

```
$ ls
cpsc-120-lab-01-your_github_team_name
```

Let's access that folder and look at the contents:

```
$ cd cpsc-120-lab-01-your_github_team_name
$ ls
AUTHORS.md README.md part-1
```

As you can see, a copy of the `README` file and the `part-1` directory that you saw on the web-view of your GitHub repository have been downloaded (cloned) into your computer. You have successfully cloned your lab assignment's git repository.

Next, let's navigate into the `part-1` directory so we can see the starter C++ code that we will use in this lab.

```
$ cd part-1
$ ls
README.md hello.cc
```

The `part-1` directory contains the file we need to edit. The remaining steps assume that you are in the `part-1` directory. If you ever type `ls` and don't see `hello.cc`, ask your partner or your instructor for help navigating back to the `part-1` directory.

### Compiling and executing code

The file `hello.cc` contains source code for the program, written in C++. Our program will print "Hello World!" in the terminal whenever it is executed. Source code must first be compiled so that it can be executed in the computer. Let's go ahead and compile the source code.

#### Compiling source code

Linux comes with the `clang++` compiler installed.

To compile the `hello.cc` source code, run the following command:

```
$ clang++ hello.cc
```

Now you will see that a new file `a.out` has been created:
```
$ ls
a.out hello.cc README.md
```

This file is the compiled version of the source code, which we call a binary file (you will learn more about this later). This file is also an executable file, which means that we can run/execute it. Let's go ahead and execute the code.

#### Executing code

To execute or run the code, you need to append the prefix `./` to the name of the binary file. Type `./a.out` in the terminal and press enter. That will run the code and print any outputs that the code generates. It should print the following:

```
$ ./a.out
Hello world!
```

Now you have successfully compiled and executed C++ code!

### Editing code

C++ source code is just a plain text file, which means that you could use a text editor to edit the contents of the file. However, because we have to make sure the contents are plain text (no different fonts, bold, underline, italics, etc), it is safer to use a code editor rather than a text editor (such as Microsoft Word or WordPad). There are many types of code editors, some are very basic and straight forward, while other comes with sophisticated features such as code coloring, code suggestions, auto-formatters, etc. [Microsoft VS Code](https://code.visualstudio.com/) is a very popular and flexible editor provided by Microsoft at no cost.

You can open VS Code by running the `code` command in the terminal. (If the shell reports `command not found` that means it is not installed. Ask your instructor for help.)

If you want to directly open the C++ source code file you want to edit, you can pass the name of the file as the first argument of the `code` command. In our case, it will be `hello.cc`:

```
$ code hello.cc
```

Now that VS Code is open, go ahead and edit the `hello.cc`. Make the following changes:

1. Replace "world" with your name, so that when you run it, it will print out your name. Let's pretend our name is Tuffy Titan, instead of printing "Hello World!" the program will print "Hello Tuffy!" after the file is saved, compiled, and run again.

To help you visualize the changes, the original `hello.cc` is shown below with each line prefixed with a line number. In C++, never type out the line numbers - it is shown here to help us talk about the code by giving each line a number we can reference. The entire program is C++ source code (lines 2-9). There are no comments or headers.

```c++
   1  
   2  #include <iostream>
   3  
   4  int main(int argc, const char *argv[]) {
   5    std::cout << "Hello World!\n";
   6    return 0;
   7  }
   8
```

The first step is to replace "world" with your name, so that when you run your program, it will print out your name.

Note that it prints out `Hello world!\n` on line 5 in the example above. We need to only change that line to complete this step. Again, let us assume our name is _Tuffy Titan_.

Change line 12 from:
```c++
  5    std::cout << "Hello World!\n";
```

to:
```c++
  5    std::cout << "Hello Tuffy!\n";
```

Next, save your changes (File menu), re-compile (`clang++ hello.cc`), and run the new program (`./a.out`).

Every time you make a change to you file, save your changes (File menu), re-compile (`clang++ hello.cc`), and run the new program (`./a.out`) with every change you make. Use the up-arrow on the keyboard to save yourself some typing.

*This is very, very important and it is worth repeating.* Every time you make a change to you file, save your changes (File menu), re-compile (`clang++ hello.cc`), and run the new program (`./a.out`) with every change you make.

If your compiler gives you a warning or error, fix it before moving on. Never move on when there are warnings or errors.

If you have warnings, errors, or anything else that is not clear, seek assistance before moving on.

### Editing AUTHORS.md

In order for your instructors to know who worked on the project, there is a file in your repository named `AUTHORS.md` which shall contain each student's name, CSU email address, and GitHub user name. This file is located at the root level of your repository.

If you are in the `part-1` directory, use the command `cd ..` to go up one directory. For example:

```
$ pwd
/home/tuffytitan/cpsc120/cpsc-120-lab-01-your_github_team_name/part-1
$ cd ..
$ pwd
/home/tuffytitan/cpsc120/cpsc-120-lab-01-your_github_team_name
$ ls
AUTHORS.md README.md part-1
```

If you are not quite sure how to navigate using the `pwd`, `ls`, and `cd` commands, that's OK. It's part of the learning for this lab. If you get stuck, as your instructor for some help.

Once you locate the `AUTHORS.md` file, use the `code` command to open it in your text editor.

```
$ code AUTHORS.md
```

The file is empty so you and your partner will fill it in. Let's imagine your name is Tuffy Titan and your partner's name is Peter Anteater. Tuffy's email address is tuffy@csu.fullerton.edu and Peter's email address is peter@csu.fullerton.edu. Peter's GitHub user name is `anteater` and Tuffy's GitHub user name is `tuffytitan`. With this information, the contents of the `AUTHORS.md` file will look like the following example:

```
Tuffy Titan
tuffy@csu.fullerton.edu
@tuffytitan
Peter Anteater
peter@csu.fullerton.edu
@anteater
```

The order matters and it is part of your grade. Please make your `AUTHORS.md` file match the same pattern as the one given here.

If you need help, please ask an instructor for guidance.

### Pushing code to GitHub (submitting your assignment)

To submit your work, you will need to add the files that you want to submit, commit your changes, and push them into the GitHub repository. This is all done using the `git` program. Your work is sent to GitHub where your instructor and view it.

#### Adding the files

From the time you cloned the repository to now, there are two changes to the folder:

1. A new file `a.out` exists
1. The `hello.cc` file was modified.
1. The `AUTHORS.md` file was modified.

You can verify this by running `git status`. If you run `git status` and you do not see `a.out` listed it is OK. The output should look like the following:

```
$ git status
On branch main
Your branch is up to date with 'origin/main'.

Changes not staged for commit:
  (use "git add <file>..." to update what will be committed)
  (use "git checkout -- <file>..." to discard changes in working directory)

	modified:   AUTHORS.md
	modified:   hello.cc

Untracked files:
  (use "git add <file>..." to include in what will be committed)

	a.out

no changes added to commit (use "git add" and/or "git commit -a")
```

That information is telling two things: there is a modification to the `hello.cc` and `AUTHORS.md` file and there is a new (untracked) file `a.out` that didn't exist before when you cloned the repository.

When submitting lab assignments or your project in this class, you will never be asked to submit the compiled code (in this case, the file `a.out`). We will take care of compiling it for you and running it for you when grading your assignment. That means that you just need to submit the `hello.cc` file.

In Git, you can only submit *commits*. A commit can be composed of multiple actions such as modifying a file, adding a new file, deleting a file. In this case, we just want to commit the modification you made to `hello.cc` and `AUTHORS.md`, so we first need to add `hello.cc` and `AUTHORS.md` to the commit by running the following command:

```
$ git add hello.cc AUTHORS.md
```

Now when you run `git status`, you will notice that the `modified: hello.cc` and `modified: AUTHORS.md` lines is under *Changes to be committed* rather than *Changes not staged for commit*.

Please note that if you only want to commit the changes to one file, you can use `git add` with only one file name. For example:

```
$ git add hello.cc
```

#### Committing your changes

To commit your changes (which in this case is was due to a single file), you run the command `git commit -m "Some quick description here"`. The `-m` indicates that the next parameter will be a description of your commit. The description should always be a sentence explaining what your change is about, and should be readable and useful for other engineers/programmers to understand what your change did. Some examples of commit descriptions could be *"Fixed bug that was causing the camera app to crash."* or *"Implemented the search feature for the project."*

In our case, you can use the description *"Changed the hello world message to show my name."* by running the following command:

```
$ git commit -m "Changed the hello world message to show my name. This is so awesome! I even recompiled it and verified that it works."
```

That command will output a message similar to this one:

```
[main 7374384] Changed the hello world message to show my name. This is so awesome! I even recompiled it and verified that it works.
 2 files changed, 10 insertions(+), 2 deletions(-)
```

Something to notice in there is the line that says `2 files changed, 10 insertions(+), 2 deletions(-)`. It is a summary of how much stuff has changed in this commit. As we know, we modified 2 files. However, it also says that there was 10 insertions and 2 deletions. Those two measures are referring to how many lines were inserted and how many lines were deleted respectively. (Your values may be very different for this exercise. It's OK to have numbers larger or smaller.) Git doesn't measure how many lines were modified, that means that if you modify a line, it will treat it as deleting that line and adding a new one with your modification.

##### Commit Warning Message

If you did not configure `git` in the first step, you will see a warning message that will look something like the following:

```
[main 7374384] Changed the hello world message to show my name. This is so awesome! I even recompiled it and verified that it works.
 Committer: Tuffy Titan <tuffy.titan@1.1.168.192.in-addr.arpa>
Your name and email address were configured automatically based
on your username and hostname. Please check that they are accurate.
You can suppress this message by setting them explicitly. Run the
following command and follow the instructions in your editor to edit
your configuration file:

    git config --global --edit

After doing this, you may fix the identity used for this commit with:

    git commit --amend --reset-author

 1 file changed, 1 insertion(+), 1 deletion(-)
```

This means that `git` does not know who you are so it made the best guess possible. Sometimes these guess are pretty good and other times they can be really poor.

The best course of action is to make sure `git` is configured correctly. Re-run the `gcf.sh` script described in **Save Your Configuration** under **Configuring Git**.


#### Pushing your commit to GitHub

The last step is to push your commit to GitHub. Pushing means that your changes are sent to GitHub and this makes your changes available for your instructors to see and grade. Running the following command will upload your commit, which includes the files you added or edited, as well as the commit message:

```
$ git push
```

If everything went well, you should see a message similar to this one:

```
Counting objects: 3, done.
Delta compression using up to 8 threads.
Compressing objects: 100% (3/3), done.
Writing objects: 100% (3/3), 340 bytes | 340.00 KiB/s, done.
Total 3 (delta 1), reused 0 (delta 0)
remote: Resolving deltas: 100% (1/1), completed with 1 local object.
To https://github.com/some-github-organization/cpsc-120-lab-01-your_github_team_name
```

If you open the URL of your Git repository, you will see a blue row right above the list of files that shows your last commit. It will say something like this:

```
your_user_name Changed the hello world message to show my name. This is so awesome! I even recompiled it and verified that it works. Latest commit 7374384  1 minute ago
```

You can try clicking on the commit number (in the example above, that would be `7374384`) to open a web-view of the commit you made.

#### GitHub Actions

Every time you push your work to GitHub, a series of actions that your instructor created are run. It may take 10 seconds or 20 minutes for these actions to complete after your push completes. Most of the time, the actions complete with in a few minutes. You can see the output of these actions by viewing the _Actions_ tab on your repository's GitHub page. This is a link between _Pull Requests_ and _Projects_.

Click on the arrow icons to see if there were any errors. This is an excellent way to determine if your work is going to get high marks or low marks. 

## Acknowledgements
This lab includes material by Jeff Li of Google.
