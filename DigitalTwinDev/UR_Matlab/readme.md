# UR5e Twin Documentation

## Setup

### MATLAB

At time of writing, MATLAB Simulink Desktop Real-Time (SLDRT) can only run within the MATLAB application.
So, you must have access to MATLAB, Simulink, and all MATLAB add-on dependencies to use the model.

MATLAB add-on dependencies:
- Simulink Desktop Real Time
- Simulink Simscape
- Simulink Simscape Multibody
- Simulink Electrical

To set up the model for use after opening it, you must first go into the "UR5e" and "Gripper" subsystems and locate all "File Solid" blocks.
MATLAB, for whatever reason, does not accept relative paths for file locations for part geometry.
For every File Solid, select the appropriate file from the project folder.
The existing filenames should make it clear which file is associated with which block.

### Processing

The Processing folder has a specific file structure:
```
Processing
|-- source (folder)
  |-- .pde files (program source files)
|-- data (folder)
  |-- config.json (configuration file)
  |-- config readme.md 
  |-- .xml files (dummy MTConnect data for testing)
|-- lib (folder)
  |-- various library files
| executable file
```

## Execution

The processing program must be running before the MATLAB simulation runs, since MATLAB will only try to connect over the nework when the simulation starts.
This also means that if there is a network disconnect, MATLAB will need to be restarted.
This is one of the multiple reasons why we should pivot away from using MATLAB for real-time applications.

So, to run the digital twin, follow these steps:

1. Ensure the config.json file for processing is properly set up
2. Open the Simulink model in MATLAB
3. Run the Processing program
4. Run the Simulink model
5. Verify that MATLAB's output matches the input from the UR5e.

## Extra Files

The "Processing (source)" folder contains the actual source files for the Processing program,
along with extra files used for testing and analysis, which can be opened with the Processing IDE.
Most of the extra files are Excel spreadsheets with recorded data from the program.
There is a file in the source folder explaining the contents of each Excel file.