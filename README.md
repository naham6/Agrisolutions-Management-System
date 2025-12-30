# Agrisolutions Management System

A comprehensive C-based management tool designed for farmers and administrators. This project was developed to demonstrate the practical application of **Linked List Data Structures**.

## 🧠 Data Structures Used
This project utilizes multiple **Singly Linked Lists** to manage data dynamically without fixed array limits:
* **User List:** Stores user credentials and profile details using a linked node structure.
* **Product List:** Manages the general marketplace inventory.
* **Farmer Product List:** Handles specific sell-posts created by farmer users.

## 🛠️ Key Features
* **User Authentication:** Sign-up and login system for users and administrators.
* **Admin Panel:** Administrative controls to add/delete products and manage registered users.
* **Marketplace Logic:** Ability to post products for sale and process purchases (updates quantities in real-time).
* **Interactive ChatBot:** A basic keyword-matching bot for user assistance.

## 📈 Technical Implementation
The project implements core CRUD (Create, Read, Update, Delete) operations on Linked Lists:
* **Dynamic Memory Allocation:** Uses `malloc` for creating new nodes.
* **Pointer Manipulation:** Efficiently traverses and updates list pointers during deletion and insertion.
* **String Processing:** Utilizes `string.h` for data comparison and management.
