# M2OEP-wchrisma
Module1 Open ended project

CS 120 Module 2 Open-Ended Project
For this project, you will design, implement, test, and use a C++ project with concepts from Module 2.
Requirements

  * Your README.md file should include:
    * Your name(s)
      * Wyatt Chrisman
    * A summary of your program, including a list of Module 2 concepts used 
      * I created a hockey based game that allows a user to draft a 5 player team and 
      go head to head against another 5 player team.  Each of these players is a child class 
      of a larger parent class (Player).  Each of these child classes have their own sayings
      as well as a multiplier on a specific stat on all but Normal.  These players go head to head
      against another team in a pokemon-esque style battle. 
      * Some topics that I used were:
        * Random for a lot of my methods
        * Is-A class relationship between player and sub-types
        * Polymorphism with the player saying

    * Any known bugs at time of submission 
      * My input validation did not work at the time of recording the video demo, I believe i have fixed it
      * Game does not always end when user runs out of players
    * Future work (how you could expand the program with more time)
      * Add more game modes, more time into these game modes
      * Visuals
      * Difficulties
      * Larger teams
      * Set Positions
    * Citations for any code not written by you or the instructor 
    * The grade you think you have earned, based on the grading rubric below, with justification
    |Module 2 Topic Added||
  * Your main program should have a clear and complex purpose. The goals and functionality of your program should inform the development and design of your class(es) and other concepts. You are highly encouraged to plan and design your main.cpp functionality before writing your other files. Put an add_executable line in CMakeLists.txt to create an executable for your main program. The program should be interactive and all user input must be validated.


| Grading Category                           | Points Deserved | Reasoning                                                                                                                                                                                 | 
|--------------------------------------------|-----------------|-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| Main program complexity and usability      | 35/40           | All code works without errors. User validation is put into place. Implementation of numerous methods to guide the game function.                                                          |
| Testing program                            | 5/20            | Began working on it, couldn't get it to run properly                                                                                                                                      |
| Concepts: Is-A or Has-A class relationship | 30/20           | Player is the main parent class, which has 5 children: Normal, Sniper, Playmaker, Fighter, and Veteran.  These children classes are similar but have an overlaoded playerSaying() method. |
| Concepts: File input or file output        | 5/5             | All Player information is read in from a csv file                                                                                                                                         |
|                                            |                 |                                                                                                                                                                                           |


    

Module 2 Concept Menu
    You can include any combination of these C++ concepts from Module 2: • Inheritance class relationship
    • Component class relationship
    • File input and/or output
    All of the concepts that you use in your main program must be clearly listed in your README.md file.

