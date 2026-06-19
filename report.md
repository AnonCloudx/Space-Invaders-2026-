PROJECT REPORT
California State University, Long Beach
Department of Computer Engineering & Computer Science
Project Title: Space Invaders 
Course: CECS 347 – Embedded Systems II
Project Number: 3
Submission Date: 05/06/2026


Table of Contents  
1. Introduction
1.1 Project Objective
1.2 System Overview
2. Requirements & Constraints
2.1 Functional Requirements
2.2 Design & Hardware Constraints
3. Design Alternatives & Architecture
3.1 Design Alternative A
3.2 Design Alternative B
3.3 Design Comparison Table
3.4 Final Design Selection & Justification
4. System Architecture
4.1 Block Diagram
4.2 Module Decomposition
4.3 Call Graph
4.4 Data Flow Diagram
4.5 Software Flowchart
5. Module Implementation & Testing
5.1 Module List and Responsibility
5.2 Module Test Strategy
5.3 Module Test Summary Table
5.4 Team Assignment
6. System Integration & Validation
6.1 Integration Order & Rationale
6.2 System-Level Test Matrix
6.3 Team Assignment
7. Claim–Evidence–Reasoning (CER)
8. Demonstration Summary
9. Conclusion
10. References


1. Introduction
1.1 Project Objective
The objective of this project was to design and implement a simplified version of the classic Space Invaders game on the TM4C123 microcontroller. The system integrates real‑time graphics, user input, timing control, collision detection, and scoring. The project demonstrates embedded systems principles including interrupt‑driven input, periodic timing, ADC‑based analog control, and modular software design.
1.2 System Overview
The game runs on the TM4C123 LaunchPad and displays graphics on a Nokia 5110 LCD. The player controls a spaceship using a slide potentiometer connected to the ADC. SW1 fires bullets, and SW2 starts the game. Enemies move horizontally across the screen, and the player must shoot them before they reach the right edge. The system uses SysTick interrupts for timing, GPIO interrupts for input, and modular software components for movement, rendering, and collision detection.
2. Requirements & Constraints
2.1 Functional Requirements
Display Requirements
• RQ‑01: Display a start screen with game title and SW2 prompt.
• RQ‑02: Display a game‑over screen and score for exactly 3 seconds.
• RQ‑03: Render the game scene at 10 Hz.
• RQ‑04: Display the current score during gameplay.
Spaceship Movement
• RQ‑05: Spaceship remains on bottom row and moves horizontally across full width.
• RQ‑06: Spaceship position updates every 0.1 seconds using ADC input.
Enemy Behavior
• RQ‑07: At least one enemy sprite must appear during gameplay.
• RQ‑08: Enemies move left‑to‑right at 1 pixel per 0.1 seconds.
• RQ‑09: Enemy is removed when reaching x = 83.
• RQ‑10: Enemy is removed when hit by a bullet.
• RQ‑11: At least three distinct enemy sprites must be used.
Bullet / Shooting System
• RQ‑12: Bullet fires from center of ship upon SW1 release.
• RQ‑13: Bullet travels upward at 1 pixel per 0.1 seconds.
• RQ‑14: Only one bullet may exist at a time.
• RQ‑15: Bullet is removed at top boundary.
• RQ‑16: Bullet is removed upon collision.
Collision Detection & Explosion
• RQ‑17: Collision detected using rectangle overlap logic.
• RQ‑18: Explosion sprite displayed for 0.1 seconds after collision.
Input Handling
• RQ‑19: SW2 begins a new game session.
• RQ‑20: SW2 resets game from game‑over screen.
• RQ‑21: SW1 fires bullet on release (rising edge).
• RQ‑22: Switches must use hardware interrupts.
Sound
• RQ‑23: Shooting sound plays when bullet fires.
• RQ‑24: Explosion sound plays when enemy is hit.
• RQ‑25: Sound output uses 4‑bit R‑2R DAC.
• RQ‑26: Sound timing controlled by hardware timer.
Game Flow
• RQ‑27: Game ends when all enemies are eliminated.
• RQ‑28: After 3‑second game‑over display, system returns to start screen.
• RQ‑29: Score increments by one per enemy hit.
2.2 Constraints
• System must run on TM4C123 microcontroller.
• Input limited to onboard switches and slide potentiometer.
• Display must use Nokia 5110 LCD via SSI.
• System must operate at real‑time speed with no visible lag.
• All timing must be interrupt‑driven (SysTick, GPIO, Timer1).
• No external processors or additional microcontrollers may be used.
• All graphics must fit within 84×48 LCD resolution.
• Only one bullet may exist at a time due to memory and timing constraints.
3. Design Alternatives & Architecture
3.1 Design Option A
Hardware: TM4C123, ADC, GPIO, SysTick, Nokia 5110.
Software: Single centralized FSM controlling all game logic.
Advantages: Simple structure.
Disadvantages: Harder to debug, tightly coupled, poor modularity.
3.2 Design Option B
Hardware: Same as Option A.
Software: Modular architecture with independent controllers for player, enemies, bullets, collisions, score, and rendering.
Advantages: Easier debugging, better team collaboration, supports Step 3 module testing.
Disadvantages: Slightly more overhead.
3.3 Design Comparison Table
Criteria 
Option A
Option B
Modularity
Low
High
Debug
Low
High
Team Collaboration 
Poor
Strong
Scalability
Limited
Good
Complexity 
Low
Moderate


3.4 Final Design Selection
Design Option B was selected because it supports modular testing, improves maintainability, and allows each team member to work independently on separate modules. It aligns with the project’s requirement for Step 3 module testing and produces cleaner, more reliable code.

4. System Architecture
4.1 Block Diagram
(Insert diagram)
4.2 Module Decomposition
 System Controller
Player Controller 
Enemy Controller
Bullet Manager 
Collision Detector 
Score Manager
LCD Renderer
Interrupt Handlers (SysTick, GPIO) 
4.3 Call Graph

4.4 Data Flow Diagram

4.5 Software Flowchart

5. Module Implementation & Testing


5.1 Module List and Responsibility
System Controller – Bijan 
Player Controller – Kairi 
Enemy Controller – Estefania 
Bullet Manager – Deshawn
 Collision Detector – Kairi
 Score Manager – Bijan 
LCD Renderer – Estefania 
5.2 Module Test Strategy
Describe how modules were tested independently.
5.3 Module Test Summary Table
Module
Test ID
Test Type
Evidence Reference
Enemy Controller
EC-02
Movement
evidence/Step3_ModuleTests/MOD-01_EnemyController_Initialization.png
Bullet Constraint
CD-04
Collision Detector
evidence/Step3_ModuleTests/MOD-07_BulletManager_Fire.png
Render
LR-05
Sprite Rendering
evidence/Step3_ModuleTests/MOD-12_Collision_InactiveBullet.png

Evidence files must match the naming convention defined in the “evidence” folder.

6. System Integration & Validation
6.1 Integration Order & Rationale
PLL → SysTick → ADC → Port F → LCD → Game_Init → Move → Draw → Interrupts 

6.2 System-Level Test Matrix

6.3 Team Assignment
All members participated in integration and validation. 
7. Claim–Evidence–Reasoning (CER)
CER‑01: Game Start
Claim: Game begins only when SW2 is pressed.
Evidence: GPIOPortF_Handler sets game_s = ON only on PF0 interrupt.
Reasoning: No other code path sets game_s = ON.

CER‑02: Player Movement
Claim: Player movement is controlled by ADC.
Evidence: Move() reads ADC_In() and maps value to 0–83.
Reasoning: ADC directly determines horizontal position.

CER‑03: Bullet Firing
Claim: Only one bullet may exist at a time.
Evidence: GPIOPortF_Handler checks Bullet.life == DEAD.
Reasoning: Prevents multiple bullets.

CER‑04: Collision Detection
Claim: Bullet‑enemy collisions are correctly detected.
Evidence: AABB overlap logic in Move().
Reasoning: Standard collision method.

CER‑05: Game Over
Claim: Game ends when all enemies are eliminated.
Evidence: num_life == 0 triggers game_s = OVER.
Reasoning: Matches requirement.
8. Demonstration Summary
Demo Scenario:
The game was demonstrated live on the TM4C123 LaunchPad with the Nokia 5110 LCD, potentiometer, and speaker connected. Four gameplay scenarios were tested in sequence. In the first run all three enemies were shot and killed, producing a final score of 3. In the second run two enemies were shot and one reached the right edge, producing a score of 2. In the third run one enemy was shot and two reached the right edge, producing a score of 1. In the fourth run all three enemies reached the right edge without being hit, producing a score of 0. In all four cases the game over screen appeared after all enemies were eliminated and displayed the correct score.
Robustness Condition Tested:
The edge case was tested by allowing the final enemy to reach the right screen boundary without being shot. This confirmed that the boundary detection logic correctly sets life = DEAD when Enemy[i].x + ENEMY10W >= 83, and that the game transitions to the OVER state even when no bullet is involved. It also confirmed that the explosion animation only triggers on bullet collision and not on boundary death.
Observed Behavior:
All four scoring scenarios produced correct results. The game over screen displayed the accurate score each time and held for approximately 3 seconds before returning to the start screen. Potentiometer control moved the ship smoothly across the x-axis. Shoot and explosion sounds triggered correctly on bullet fire and enemy collision, respectively. No audio artifacts or display glitches were observed during any of the four runs. 

 Link:
https://www.youtube.com/channel/UC3x8JKv7GXLOvzhwrGujxHQ 
9. Conclusion
• Summary of technical achievements
• Major challenges and solutions
• Key lessons learned
10. References
Valvano, J. Embedded Systems: Real‑Time Interfacing to ARM Cortex‑M Microcontrollers.
TM4C123GH6PM Datasheet
Nokia 5110 LCD Documentation 
CECS 347 Course Materials
Team‑generated test evidence and debug logs 


