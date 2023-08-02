# Shoe Inventory Management with File Handling

This repository contains a simple shoe inventory management system implemented in C, utilizing file handling to store and manipulate the data. The program allows users to perform CRUD operations (Create, Read, Update, Delete) on shoe records and stores the data in the "inventory.txt" file.

## How to Use

1. **Clone the repository:** 
   ```
   git clone https://github.com/your-username/ShoeInventory_FileHandling.git
   cd ShoeInventory_FileHandling
   ```

2. **Compile and run the program:**
   ```
   gcc shoe_inventory.c -o shoe_inventory
   ./shoe_inventory
   ```

3. **Using the program:**
   - Upon running the program, a menu will be displayed with options to create, read, update, or delete shoe records in the inventory.
   - The shoe records will be stored in the "inventory.txt" file and can be accessed for further operations.

## Functionality

The program provides the following functions:

1. **Create a New Shoe Record:** Users can input details like stock number, style number, prices, and the number of pairs for each size (3 - 14). The record will be added to the "inventory.txt" file.

2. **Read Shoe Records:** Users can choose to display all shoe records or search for a specific shoe using stock and style numbers.

3. **Update Shoe Records:** Users can update either the price or the number of pairs for a specific shoe size.

4. **Delete Shoe Records:** Users can delete a specific shoe record by providing its stock and style numbers or delete the entire inventory.

## Shoe Structure

The shoe records are stored in the "inventory.txt" file with the following format:

```
StockNumber StyleNumber Sizes[12] Price
```

## Example

An example of the "inventory.txt" file with shoe records:

```
1001 5 10 8 13 7 0 0 20 14 6 12 0 89.99
2002 3 5 10 2 15 8 0 0 22 9 14 11 59.99
```

## Contributions

Contributions to enhance the functionality, improve the user interface, or fix bugs are welcome! Please create a pull request, and we'll be glad to review it.

---

This README provides a brief overview of the "ShoeInventory_FileHandling" repository, instructions on how to use the code, details about the shoe inventory management program, the file structure, an example of the "inventory.txt" file, information on contributing, and the license information. Feel free to expand on each section to provide more comprehensive details and explanations.
