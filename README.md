# 🌟 NotinoOOP - Console Fragrance Shop System

This project is a comprehensive object-oriented console system for managing a fragrance shop, written in modern C++. The project simulates real-world business logic, including inventory management, user profiles, recommendation algorithms, and dynamic discount calculations.

## 🚀 Core Features

The system supports two main types of users, each with their own permissions and commands:

### 👤 Buyers
- **Shopping:** Adding fragrances to the cart, viewing, and finalizing the order (`checkout`).
- **Smart Discounts:** During checkout, the system automatically calculates and applies the best available discount for the user.
- **Recommendation Algorithm (`recommend`):** Analyzes products in the client's `wishlist` and automatically suggests new fragrances from the same scent category.
- **Reviews:** Ability to rate and write comments on purchased fragrances.
- **Fund Management:** Adding a virtual balance and tracking order history (pending, delivered, or canceled).

### 🛡️ Admins
- **Catalog Management:** Creating new fragrances (with brand, fragrance family, and price) and adding stock quantities.
- **Moderation:** Removing inappropriate reviews.
- **Automatic Penalties:** If 7 reviews of a given user are deleted, the system automatically blocks and deletes their profile.
- **Deliveries:** Changing the status of client orders to "Delivered".

---

## 🧠 Technologies and OOP Concepts Used

The project demonstrates a solid understanding of Object-Oriented Programming (OOP) principles and design patterns:

- **Command Design Pattern:** All user actions are encapsulated into separate commands via the `CommandFactory` and the `ICommand` interface. This keeps the main program loop exceptionally clean and highly scalable.
- **Polymorphism:** Used in handling users (pointers to the base `User` class) and in calculating discounts (base `Discount` class with virtual methods, inherited by `BonusDiscount` and `BrandDiscount`).
- **Memory Management:** Extensive use of `std::unique_ptr` for safe object lifecycle management and preventing memory leaks.
- **File System:** Automatic saving (`saveData`) and loading (`loadData`) of the shop's state (catalog and users) into local `.txt` files upon program startup and shutdown.
- **Modern C++:** Utilization of libraries like `<print>` (for `std::println`), `<random>` (for shuffling recommendations), and `std::erase_if` for optimized searching and element deletion.

---

## 🛠️ How to Run the Project

1. Clone the repository to your local machine:
   
```bash
   git clone [https://github.com/slaveyametodieva/NotinoOOP.git](https://github.com/slaveyametodieva/NotinoOOP.git)

   ## 🎮 Example Execution (Test Scenario)

If you want to test the full functionality of the system right after compiling, you can enter the following commands line by line in the console:

### Step 1: Loading the Shop (Admin Panel)
On first launch, the system is empty. We log in with the admin profile to populate the fragrance catalog:

```text
login admin admin123
create-fragrance Libre 9 100.00 1
create-fragrance Jadore 4 120.00 1
add-quantity Libre 20
add-quantity Jadore 15
logout
```

### Step 2: Client Panel:
```text
register sofia pass1
login sofia pass1
add-to-wishlist Libre
recommend
make-review Libre 5 "Amazing_scent!"
add-to-balance 300
add-to-cart Libre
add-to-cart Jadore
view-cart
checkout
view-purchases
exit
