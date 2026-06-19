# Step 1 – Requirements & Constraints

## Functional Requirements
## Display Requirements

RQ-01 - The system shall display a start screen containing the game title and a prompt to press SW2 to begin. TESTMETHOD- Visual Inspection of the LCD
RQ-02 - The system shall display a 'game over' screening and the plays numeric score for exactly 3 seconds before returning to the start screen. TEST METHOD - observe screen content and time transition
RQ-03 - THe system shall render the game scene ( spaceship, enemies and bullets) in real time updating the nokia 5110 LCD screen every .01 seconds = 10HZ . TESTMETHOD confirm 10hz with logic analyzer on SSII lines or by counting frames over 1 second
RQ-04 The system shall display the current score as an intiger on the active game screen. TESTMETHOD - Elimate enemies and verify score increments correctly on screen.

## Spaceship Movement

RQ-05 - The spaceship shall be positioned at the bottom row of the LCD and should move horizontally across the full display width. TEST METHOD - Rotate potentionmeter end to end; verify spaceship spans x0-x53
RQ-06 - The spaceship position shall be updated via ADC reading on every game update cycle (every0.1 seconds) TESTMETHOD- observe spaceship movement responsiveness relative to potentiometer

## Enemy Behavior

RQ-07- The system shall display at least one enemy sprite on screen during active gameplay. TESTMETHOD- Visual inspection during game session.
RQ-08 - Each enemy shall move from left to right at a rate of 1 pixel per 0.1 seconds (10 pixels per second). TESTMETHOD -Track enemy x-position over 1 second using debug output or visual observation; 
RQ-09 - An enemy shall be eliminated (removed from the display) if it reaches the right edge of the screen (x=83). TEST METHOD - Allow enemy to traverse the screen without shooting; confirm it disappears at the right edge.
RQ-10 - An enemy shall be eliminated if it is struck by the player's bullet (collision detected). TEST METHOD - Fire bullet at an enemy; confirm enemy is removed upon overlap.
RQ-11 - The game shall use at least 3 distinct enemy sprite designs. TEST METHOD - Visual inspection; confirm visual differences among enemy types.

## Bullet / Shooting System

RQ-12 - A bullet shall be fired from the horizontal center of the top edge of the spaceship sprite upon release of SW1. TEST METHOD - Press and release SW1; confirm bullet originates from the correct position.
RQ-13 - The bullet shall travel upward at a rate of 1 pixel per 0.1 seconds. TEST METHOD - Observe bullet movement over 1 second; confirm 10-pixel upward displacement.
RQ-14 - No more than one bullet shall exist on screen at any given time. TEST METHOD - Rapidly press SW1 multiple times; confirm only one bullet is visible simultaneously.
RQ-15 - The bullet shall be removed from the screen when it reaches the top boundary of the display. TEST METHOD - Fire bullet with no enemies present; confirm it disappears at the top edge.
RQ-16 - The bullet shall be removed from the screen upon collision with an enemy. TEST METHOD - Fire bullet at an enemy; confirm bullet disappears on contact.

## Collision Detection & Explosion 

RQ-17 - The system shall detect a collision between the bullet and an enemy using rectangle overlap logic. TEST METHOD - Fire bullet at enemy and confirm enemy is eliminated upon spatial overlap.
RQ-18 - Upon a bullet-enemy collision, the system shall display an explosion sprite at the location of the eliminated enemy for exactly 0.1 seconds (one game update cycle), replacing the enemy image. TEST METHOD - Fire at enemy; time the explosion display duration.

## Input Handling

RQ-19 - Pressing SW2 on the start screen shall begin a new game session. TEST METHOD - Press SW2 on start screen; confirm transition to active game.
RQ-20 - SW2 shall reset the game when pressed on the game-over screen or after game completion. TEST METHOD - Allow game to reach game-over screen; press SW2; confirm return to start screen.
RQ-21 - SW1 shall fire a bullet upon switch release (rising-edge detection after press). TEST METHOD - Press and hold SW1, then release; confirm bullet fires at moment of release, not press.
RQ-22 - Switch inputs (SW1, SW2) shall be handled via edge-triggered hardware interrupts, not polling. TEST METHOD - Inspect source code for ISR registration; verify NVIC configuration.

## Sound

RQ-23 - The system shall produce an audible shooting sound effect when a bullet is fired. TEST METHOD - Fire bullet; confirm distinct sound is heard through speaker.
RQ-24 - The system shall produce an audible enemy-hit sound effect when a bullet collides with an enemy. TEST METHOD - Shoot an enemy; confirm distinct sound different from shooting sound is heard.
RQ-25 - Sound output shall be generated using a 4-bit R-2R DAC connected to TM4C123 GPIO pins. TEST METHOD - Inspect schematic and wiring; verify 4 resistor ladder stages; measure stepped analog output on oscilloscope.
RQ-26 - Sound timing shall be controlled by a hardware timer, not software delays. TEST METHOD - Inspect source code; verify sound ISR is driven by hardware timer register.

## Game Flow

RQ-27 - The game shall end when all enemies have been eliminated from the screen (either shot or reached the right edge). TEST METHOD - Eliminate all enemies; confirm game-over screen appears.
RQ-28 - After the 3-second game-over display, the system shall automatically return to the start screen. TEST METHOD - Time the game-over display duration; confirm automatic return to start screen.
RQ-29 - The score shall increment by one each time an enemy is eliminated by a bullet hit. TEST METHOD - Shoot multiple enemies; verify score counter reflects the correct count.


## Constraints
## Hardware Constraints

- CN-01: The system must be implemented on the Nexys A7 FPGA board.
- CN-02: Input shall be limited to onboard pushbuttons and switches.
- CN-03: The display output shall use the VGA port available on the board.
- CN-04: The system must operate within the FPGA’s available logic resources (LUTs, flip-flops).
- CN-05: The design must use the onboard clock signal provided by the Nexys A7.
- CN-06: The system must interface with hardware using Verilog HDL only.
- CN-07: No external hardware components (e.g., external controllers or sensors) shall be used.
- CN-08: The system must operate in real-time without noticeable delay.
- CN-09: All outputs must be visible through onboard LEDs or VGA display.

## Traceability

This project will maintain traceability by assigning unique identifiers to all requirements (RQ-##) and constraints (CN-##). 

Each functional requirement will be mapped to corresponding design modules, implementation components, and test cases in later project steps. This ensures that every requirement can be verified and validated.

Constraints (CN-##) will guide design decisions and will be referenced throughout development to ensure compliance with hardware and system limitations.

A traceability mapping table will be developed in future steps to link:
- Requirements (RQ-##)
- Design modules
- Implementation files
- Test cases
- 
## AI Verification Summary

AI was used only to verify and cross‑check our requirements, not to generate them. After drafting the functional requirements and constraints ourselves, we used AI to confirm that our categories—display, movement, enemies, bullets, collision logic, input handling, sound, and game flow—were complete and aligned with typical embedded game designs. Any AI‑suggested items were accepted only if they matched our hardware capabilities and project specification. No requirement was added solely because AI proposed it; all final requirements were validated by the team.
