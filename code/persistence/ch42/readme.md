# Chapter 42: Crash Consistency: FSCK and Journaling  

## Homework (Simulation)  

This section introduces fsck.py, a simple simulator you can use to better understand how file system corruptions can be detected (and potentially repaired). Please see the associated README for details on how to run the simulator.  

## Questions  

### 1. First, run fsck.py -D; this flag turns off any corruption, and thus you can use it to generate a random file system, and see if you can determine which files and directories are in there. So, go ahead and do that! Use the -p flag to see if you were right. Try this for a few different randomly-generated file systems by setting the seed (-s) to different values, like 1, 2, and 3.  


### 2. Now, let’s introduce a corruption. Run ./fsck.py -S 1 to start. Can you see what inconsistency is introduced? How would you fix it in a real file system repair tool? Use -c to check if you were right.