# Bookstore Inventory Management System

This is a terminal-based inventory management system for a bookstore, implemented in C++ using an Object-Oriented Programming (OOP) approach. The system manages books, magazines, customers, and employees (managers and cashiers). It provides features for inventory management, sales, and a loyalty points system.

---

## Features

### Customers
- **Browse Items**: Explore available books and magazines in the store.
- **Add to Cart**: Select items to add to a virtual shopping cart.
- **Checkout**: Purchase items, earning loyalty points based on the total amount spent.

### Store Manager
- **Inventory Management**:
  - Add new books and magazines to the inventory.
  - Restock existing items.
  - Update the cost or price of items.
- **Profit Tracking**: View the store's total profit.
- **Employee-Only Access**: Customers cannot directly modify the inventory.

### General Features
- **Loyalty Points System**: Customers earn points with every purchase.
- **Terminal-Based Interface**: Login as either a customer or manager.
- **Role-Based Access**: Functionalities are restricted based on the logged-in role.

---

## Classes and Design

The project consists of seven header (`.hpp`) files, each representing a distinct class:

1. **Item**  
   Base class for items in the store.  
   **Attributes**: `id`, `title`, `publisher`, `cost`, `price`, `stock`.  

2. **Book** (Derived from `Item`)  
   Represents books with additional attributes.  
   **Attributes**: `isbn`, `author`, `genre`, `pages`.  

3. **Magazine** (Derived from `Item`)  
   Represents magazines with additional attributes.  
   **Attributes**: `issue`.  

4. **Customer**  
   Represents customers of the bookstore.  
   **Attributes**: `name`, `email`, `points`.  

5. **Employee**  
   Base class for employees.  
   **Attributes**: Shared access to inventory (`books` and `magazines` vectors) and profit tracking.  

6. **Manager** (Derived from `Employee`)  
   Represents the store manager with exclusive permissions.  
   **Attributes**: `name`, `manager_id`.  
   **Actions**: Add/restock items, update prices/costs, view profits.  

7. **Cashier** (Derived from `Employee`)  
   **Actions**: Utility class handling whatever functionalities are provided to the customer in the frontend including checkout, exploring, and the loyalty point system.  

---

## How to Use

1. **Clone the Repository**  
   Clone the repository to your local machine.  

2. **Compile the Program**  
   Compile the `main.cpp` file along with the header files using a C++ compiler:  
   ```bash
   g++ main.cpp -o bookstore
   ```

3. **Run the Program**  
   Execute the compiled program:  
   ```bash
   ./bookstore
   ```

4. **Login**  
   Choose to log in as either a customer or store manager.  

5. **Explore and Interact**  
   - Customers can browse items, add to cart, and checkout.  
   - Managers can manage the inventory and view profits.  

---

## Future Improvements
- Implement a graphical user interface (GUI).
- Add support for saving and loading inventory/customer data from files.
- Enhance the loyalty points system with more tiers and rewards.
- Include reports for sales and inventory trends.

---

## Dependencies
- C++ Standard Library (`<iostream>`, `<vector>`, `<string>`).
