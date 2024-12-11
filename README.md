# ADT Visualization Project

This project allows you to interact with and visualize various Abstract Data Structures (ADTs) like Heap, Binary Search Tree (BST), Stack, Queue, Priority Queue, AVL Tree, and Red-Black Tree using SFML for graphical rendering.

**Firstly**

Ensure that you have the following installed:
- SFML (Simple and Fast Multimedia Library)
  - For Ubuntu/Debian: `sudo apt-get install libsfml-dev`
  - For macOS: `brew install sfml`
  - For Windows, download the SFML library from the [SFML website](https://www.sfml-dev.org/download.php) and follow the setup instructions.

- **g++ Compiler** (or another C++ compiler)

- **Font files**: Make sure that Oswald.ttf is available in the project directory for the menu display.

## Steps to Compile and Run the Project

### 1. Clone the Repository (if applicable)

**WARNING: For some reason, the menu doesn't display, but it's navigable. The answers will show in the terminal, AS WELL AS, if you pick Stack/AVL/BST/RedBlack. Insert the numbers necessary in the terminal, and press 3 to visualize. A new window should pop up and actually display the ADTs.

Clone this repository to your local machine:

```bash
git clone https://github.com/kitzki/FinalProject
cd FinalProject

sudo apt-get install libsfml-dev

Use the following g++ command to compile the project files:
g++ AVL.cpp BST.cpp main.cpp PriorityQueue.cpp Queue.cpp RedBlack.cpp Stack.cpp Heap.cpp -o MOD -lsfml-window -lsfml-system -lsfml-graphics

After compilation, run the program using the following command:
./MOD or ./main

Features
Menu Navigation: A simple SFML-based menu to interact with various ADTs.
Interactive Operations: Insert, Delete, Search, and display ADTs such as Heap, BST, Stack, Queue, Priority Queue, AVL Tree, and Red-Black Tree.
Visualization: Graphical visualization of data structures (Stack, Queue, AVL, Red-Black Tree).
