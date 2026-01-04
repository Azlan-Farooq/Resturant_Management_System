#include <iostream>
#include <conio.h>   // TO USE getch()
#include <windows.h> // FOR COLOURING
#include <fstream>   // FOR FILE HANDLING  [ifstream , ofstream]
#include <string>    // TO MANIPULATE STRING
#include <iomanip> // FOR  left , right  setw() [set width from left and right]
#include <ctime>   // FOR  time_t now = time(0) , tm *localTime = localtime(&now) & strftime(dateTime, sizeof(dateTime), "%A, %d %B %Y - %I:%M %p", localTime);
using namespace std;

string password = "159951";

void name_interface();
void admin(int &i, string inventory[1000], double prices[1000], double &todayRevenue,
           string orderNames[1000], double orderAmounts[1000], int orderQty[1000], int &orderCount,
           string customerNames[1000], string billDateTime[1000], double billTotals[1000], int billCount);
void admin_interface(int &i, string inventory[1000], double prices[1000], double &todayRevenue,
                     string orderNames[1000], double orderAmounts[1000], int orderQty[1000], int &orderCount, string customerNames[1000], string billDateTime[1000],
                     double billTotals[1000], int &billCount);
void user(int &i, string inventory[1000], double prices[1000], string orderNames[1000],
          double orderAmounts[1000], int orderQty[1000], int &orderCount, double &todayRevenue, string customerNames[1000], string billDateTime[1000],
          double billTotals[1000], int &billCount);
void setColor(int x);

void DefaultMenu(int &i, string inventory[1000], double prices[1000])
{
    if (i == 0)
    {
        ifstream file;   // ifstream() is used to READ data from FILE.
        file.open("Menu.txt");
        string line;
        while (getline(file, line))
        {
            string name = "";
            string price = "";
            int coma = 0;
            for (int j = 0; j < line.length(); j++)
            {

                if (line[j] == ',')
                {
                    coma = j;
                    break;
                }
            }

            for (int k = 0; k < coma; k++)
            {
                name += line[k]; // GIVING NAME
            }
            inventory[i] = name;

            for (int k = coma + 1; k < line.length(); k++)
            {
                price += line[k]; // GIVING PRICE
            }
            prices[i] = stod(price); // stod() is used to Convert String to Double (stod) data type .

            i++;
        }

        file.close();
    }
}

void SaveMenu(int i, string inventory[1000], double prices[1000])
{
    ofstream file("Menu.txt"); // THIS FUNCTION HELP TO WRITE DATA INTO FILE .
    for (int x = 0; x < i; x++)
    {
        file << inventory[x] << "," << prices[x] << endl;
    }
    file.close();
}

void SORTED_MENU(int i, string inventory[1000], double prices[1000])
{
    for (int pass = 0; pass < i - 1; pass++)
    {
        for (int j = 0; j < i - pass - 1; j++)
        {
            if (prices[j] > prices[j + 1])
            { // BUBBLE SORTING
                double tempPrice = prices[j];
                prices[j] = prices[j + 1];
                prices[j + 1] = tempPrice;

                string tempName = inventory[j];
                inventory[j] = inventory[j + 1];
                inventory[j + 1] = tempName;
            }
        }
    }
}

void displaySortedMenu(int i, string inventory[1000], double prices[1000])
{
    SORTED_MENU(i, inventory, prices);
    cout << "\n*********** MENU [Sorted by Price] ********\n";
    for (int x = 0; x < i; x++)
    {
        cout << x + 1 << ". " << inventory[x] << " - Rs. " << prices[x] << endl;
    }
}

int main()
{
    string inventory[1000];
    double prices[1000] = {0.0};
    int i = 0;

    // USER ORDER & REVENUE
    string orderNames[1000];
    double orderAmounts[1000];
    int orderQty[1000];
    int orderCount = 0;
    double todayRevenue = 0.0;

    string customerNames[1000];
    string billDateTime[1000];
    double billTotals[1000];
    int billCount = 0; // HOW many Bill Today

    DefaultMenu(i, inventory, prices);
    system("chcp 65001 >nul");

    while (true)
    {
        system("cls");
        name_interface();
        int choice;
        cout << "1. ADMIN LOGIN\n";
        cout << "2. USER LOGIN\n";
        cout << "3. EXIT\n";
        cout << "Enter Your Choice : ";

        if (!(cin >> choice))
        {
            cin.clear();
            cin.ignore(1000, '\n');
            continue;
        }

        if (choice == 1)
            admin(i, inventory, prices, todayRevenue, orderNames, orderAmounts, orderQty, orderCount,
                  customerNames, billDateTime, billTotals, billCount);
        else if (choice == 2)
            user(i, inventory, prices, orderNames, orderAmounts, orderQty, orderCount, todayRevenue,
                 customerNames, billDateTime, billTotals, billCount);
        else if (choice == 3)
            break;
    }
    return 0;
}

void setColor(int x)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), x);
}

void name_interface()
{
    setColor(5);
    cout << "██████╗ ███████╗███████╗████████╗ █████╗ ██╗   ██╗██████╗  █████╗ ███╗   ██╗████████╗" << endl;
    cout << "██╔══██╗██╔════╝██╔════╝╚══██╔══╝██╔══██╗██║   ██║██╔══██╗██╔══██╗████╗  ██║╚══██╔══╝" << endl;
    cout << "██████╔╝█████╗  ███████╗   ██║   ███████║██║   ██║██████╔╝███████║██╔██╗ ██║   ██║   " << endl;
    cout << "██╔══██╗██╔══╝  ╚════██║   ██║   ██╔══██║██║   ██║██╔══██╗██╔══██║██║╚██╗██║   ██║   " << endl;
    cout << "██║  ██║███████╗███████║   ██║   ██║  ██║╚██████╔╝██║  ██║██║  ██║██║ ╚████║   ██║   " << endl;
    cout << "╚═╝  ╚═╝╚══════╝╚══════╝   ╚═╝   ╚═╝  ╚═╝ ╚═════╝ ╚═╝  ╚═╝╚═╝  ╚═╝╚═╝  ╚═══╝   ╚═╝   " << endl;
    setColor(10);
    cout << "              ═══ M A N A G E M E N T   S Y S T E M ═══" << endl;
    setColor(14);
}
// ---------------------------- ADMIN PASSWORD SECURITY --------------------------------
void admin(int &i, string inventory[1000], double prices[1000], double &todayRevenue,
           string orderNames[1000], double orderAmounts[1000], int orderQty[1000], int &orderCount, string customerNames[1000],
           string billDateTime[1000], double billTotals[1000], int billCount)
{
    system("cls");
    name_interface();
    string passcode = "";

    while (true)
    {
        passcode = "";
        cout << "\nENTER PASSWORD (or 'B' to Go Back): ";
        char c;
        while ((c = getch()) != 13)
        {
            if (c == '\b')
            {
                if (!passcode.empty())
                {
                    passcode.pop_back();
                    cout << "\b \b";
                }
            }
            else
            {
                passcode.push_back(c);
                cout << '*';
            }
        }
        if (passcode == password)
        {
            admin_interface(i, inventory, prices, todayRevenue, orderNames, orderAmounts, orderQty, orderCount,
                            customerNames, billDateTime, billTotals, billCount);
            break;
        }
        else if (passcode == "b" || passcode == "B")
            break;
        else
        {
            setColor(12);
            cout << "\nWRONG PASSWORD\nPress any key to try again...";
            getch();
            system("cls");
            name_interface();
        }
    }
}

// _________________________________________________________________________________
// -------------------------------- ADMIN INTERFACE --------------------------------
// _________________________________________________________________________________

void admin_interface(int &i, string inventory[1000], double prices[1000], double &todayRevenue,
                     string orderNames[1000], double orderAmounts[1000], int orderQty[1000], int &orderCount, string customerNames[1000], string billDateTime[1000],
                     double billTotals[1000], int &billCount)
{
    while (true)
    {
        system("cls");
        name_interface();
        int choice;
        cout << "1. VIEW ITEMS\n";
        cout << "2. ADD ITEM\n";
        cout << "3. DELETE ITEM\n";
        cout << "4. EDIT PRICES\n";
        cout << "5. VIEW TODAY'S REVENUE\n";
        cout << "6. SWITCH TO USER\n";
        cout << "7. EXIT TO MAIN MENU\n";
        cout << "Enter Your Choice : ";
        if (!(cin >> choice))
        {
            cin.clear();
            cin.ignore(1000, '\n');
            continue;
        }

        switch (choice)
        {
        case 1:
            system("cls");
            name_interface();
            if (i == 0)
                cout << "No items in inventory.\n";
            else
                displaySortedMenu(i, inventory, prices);
            cout << "\nPress any key to return...";
            getch();
            break;

        case 2:
            system("cls");
            name_interface();
            {
                int count;
                cout << "How many Items You want to Enter : ";
                cin >> count;
                cin.ignore(1000, '\n');
                for (int j = 0; j < count; j++)
                {
                    if (i >= 1000)
                        break;
                    cout << "\nEnter name for Item " << i + 1 << " : ";
                    getline(cin, inventory[i]);
                    cout << "Enter price: ";
                    cin >> prices[i];
                    i++;
                    cin.ignore(1000, '\n');
                }
                SaveMenu(i, inventory, prices); // THIS ALLOW TO DO CHANGINGS IN FILE
            }
            break;

        case 3:
            system("cls");
            name_interface();
            if (i == 0)
            {
                cout << "No items to delete.";
                getch();
                break;
            }
            int delIndex;
            cout << "Enter item number to DELETE (1-" << i << ") : ";
            cin >> delIndex;
            if (delIndex >= 1 && delIndex <= i)
            {
                for (int k = delIndex - 1; k < i - 1; k++)
                {
                    inventory[k] = inventory[k + 1]; // THIS OVERWRITE THE VALUES BY SHIFTING.
                    prices[k] = prices[k + 1];
                }
                i--;
                cout << "Deleted.";
                SaveMenu(i, inventory, prices); // THIS ALLOW US TO DO CHANGINGS INTO THE FILE.
            }
            cout << "\nPress any key to Exit.....";
            getch();
            break;

        case 4:
            system("cls");
            name_interface();
            displaySortedMenu(i, inventory, prices);
            int editIndex;
            cout << "Enter item number to edit: ";
            cin >> editIndex;
            if (editIndex >= 1 && editIndex <= i)
            {
                cout << "New price for " << inventory[editIndex - 1] << ": ";
                cin >> prices[editIndex - 1];
                SaveMenu(i, inventory, prices); // THIS ALLOW US TO DO CHANGINGS INTO THE FILE.
            }
            cout << "\nPress any Key to return.....";
            getch();
            break;

        case 5:
            system("cls");
            name_interface();
            if (billCount == 0)
            {
                cout << "No bills recorded today.\n";
            }
            else
            {
                cout << "\n*********** TODAY'S BILLS ***********\n";
                for (int b = 0; b < billCount; b++)
                {
                    cout << "\n--- Bill " << (b + 1) << " ---\n";
                    cout << "Customer: " << customerNames[b] << "\n";
                    cout << "Time: " << billDateTime[b] << "\n";
                    cout << "Total: Rs. " << static_cast<int>(billTotals[b]) << "\n";
                } // WE USE static_cast<int> to convert double to int , to ignore .000000
                cout << "\n====================================\n";
                cout << "GRAND TOTAL REVENUE: Rs. " << static_cast<int>(todayRevenue) << "\n";
            }
            cout << "\nPress any key to return...";
            getch();
            break;

        case 6:
            user(i, inventory, prices, orderNames, orderAmounts, orderQty, orderCount, todayRevenue,
                 customerNames, billDateTime, billTotals, billCount);
            break;

        case 7:
            return;

        default:
            setColor(12); // FOR RED COLOR
            cout << "Invalid choice.";
            setColor(14);
            getch();
            break;
        }
    }
}

// _________________________________________________________________________________
// -------------------------------- USER INTERFACE --------------------------------
// _________________________________________________________________________________

void user(int &i, string inventory[1000], double prices[1000], string orderNames[1000],
          double orderAmounts[1000], int orderQty[1000], int &orderCount, double &todayRevenue,
          string customerNames[1000], string billDateTime[1000],
          double billTotals[1000], int &billCount)
{
    while (true)
    {
        system("cls");
        name_interface();
        int choice;
        cout << "1. VIEW MENU\n";
        cout << "2. PLACE ORDER\n";
        cout << "3. TAKE BILL\n";
        cout << "4. VIEW CART / REMOVE ITEMS\n";
        cout << "5. EXIT TO MAIN MENU\n";
        cout << "Enter Your Choice : ";
        if (!(cin >> choice))
        {
            cin.clear();
            cin.ignore(1000, '\n');
            continue;
        }

        switch (choice)
        {
        case 1:
            system("cls");
            name_interface();
            displaySortedMenu(i, inventory, prices);
            cout << "\nPress any key...";
            getch();
            break;

        case 2:
            system("cls");
            name_interface();
            displaySortedMenu(i, inventory, prices);
            int itemNo, qty;
        ORDER:  // <--------------------------------------------------------------
            cout << "\nEnter ITEM Number to order: ";
            cin >> itemNo;
            if (itemNo < 1 || itemNo > i)
            { 
                setColor(12);
                cout << "Invalid.";
                setColor(14);
                cout<<"\nPress any Key to return.....";
                getch();
                break;
            }
            cout << "Enter Quantity: ";
            cin >> qty;
            if (qty > 0)
            {
                orderNames[orderCount] = inventory[itemNo - 1];
                orderQty[orderCount] = qty;
                orderAmounts[orderCount] = prices[itemNo - 1] * qty;
                orderCount++;
                cout << "Added. Add more? (Y/N): ";
                char ch = getche();
                if (ch == 'y' || ch == 'Y')
                {
                    goto ORDER; // ---------------------------------------------->
                }
            }
            break;

        case 3:
        {
            system("cls");
            name_interface();
            if (orderCount == 0)
            {
                cout << "Cart empty.";
                getch();
                break;
            }

            // GETTING CUSTOMER NAME
            string customerName;
            cout << "\nEnter Customer Name: ";
            cin.ignore(); // clear newline from previous input
            getline(cin, customerName);

            // FOR CURRENT DATE AND TIME
            time_t now = time(0);            // GIVE US TIME IN SECONDS [BIG VALUE]
            tm *localTime = localtime(&now); // Convert that TIME into readable parts [year, month, day, hour, etc.]
            char dateTime[100];
            strftime(dateTime, sizeof(dateTime), "%A, %d %B %Y - %I:%M %p", localTime);
            /*strftime() = "string format time
            It builds a custom string from the localTime data
            %A--->WEEKDAY  ,   %d---->DAY OF MONTH   ,   %B---->MONTH NAME
            %Y--->YEAR     ,   %I---->HOURS   ,  %M--->MINUTES  ,  %p AM / PM
             (eg : MONDAY , 28 MAY 2025 - 06:36 PM)      */

            double total = 0.0;
            for (int idx = 0; idx < orderCount; idx++)
            {
                total += orderAmounts[idx];
            }

            system("cls");
            name_interface();
            cout << "\n";
            cout << "================== BILL ==================\n";
            cout << "Customer: " << customerName << "\n";
            cout << "Date & Time: " << dateTime << "\n";
            cout << "---------------------------------------------\n";
            cout << left << setw(25) << "Item" << right << setw(15) << "Amount" << "\n"; // setw()-->SET WIDTH
            cout << "---------------------------------------------\n";

            for (int idx = 0; idx < orderCount; idx++)
            {
                string item = orderNames[idx] + " x" + to_string(orderQty[idx]);
                cout << left << setw(25) << item
                     << right << setw(15) << ("Rs. " + to_string((int)orderAmounts[idx])) << "\n";
            }

            cout << "---------------------------------------------\n";
            cout << left << setw(25) << "TOTAL"
                 << right << setw(15) << ("Rs. " + to_string((int)total)) << "\n";
            cout << "=============================================\n";

            cout << "\nConfirm Payment? (Y/N): ";
            char ch = getche();

            if (ch == 'y' || ch == 'Y')
            {
                todayRevenue += total;

                // STORE IN ARRAYS [For Admin View]
                if (billCount < 1000)
                {
                    customerNames[billCount] = customerName;
                    billDateTime[billCount] = string(dateTime);
                    billTotals[billCount] = total;
                    billCount++;
                }

                // FOR STORING DATA TO (Revenue.txt) FILE.
                ofstream File("Revenue.txt", ios::app);
                File << "=============================================\n";
                File << "Customer: " << customerName << "\n";
                File << "Date & Time: " << dateTime << "\n";
                File << "---------------------------------------------\n";
                for (int idx = 0; idx < orderCount; idx++)
                {
                    File << orderNames[idx] << " x" << orderQty[idx] << " = Rs. " << static_cast<int>(orderAmounts[idx]) << "\n";
                } // WE USE static_cast<int> to convert double to int , to ignore .000000
                File << "---------------------------------------------\n";
                File << "TOTAL: Rs. " << static_cast<int>(total) << "\n";
                File << "=============================================\n\n";
                File.close();
                orderCount = 0;
                cout << "\n\nPayment Successful! THANK YOU.\n";
                cout << "=============================================\n";
                Sleep(2000);
            }
            else
            {
                setColor(12); // FOR RED COLOR
                cout << "\n\nPayment Cancelled.\n";
                setColor(14);
                Sleep(1000);
            }
            break;
        }

        case 4:
            while (true)
            {
                system("cls");
                name_interface();
                if (orderCount == 0)
                {
                    cout << "Cart empty.";
                    getch();
                    break;
                }
                double subtotal = 0.0;
                for (int idx = 0; idx < orderCount; idx++)
                {
                    cout << idx + 1 << ". " << orderNames[idx] << " x" << orderQty[idx] << " = Rs. " << orderAmounts[idx] << endl;
                    subtotal += orderAmounts[idx];
                }
                cout << "\nSubtotal: " << subtotal << "\nRemove item? (Y/N): ";
                char ch;
                ch = getche();
                if (ch != 'y' && ch != 'Y')
                    break;

                int remIdx, remQty;
                cout << "\nItem No: ";
                cin >> remIdx;
                cout << "Quantity to remove: ";
                cin >> remQty;

                if (remIdx >= 1 && remIdx <= orderCount)
                {
                    int idx = remIdx - 1;
                    if (remQty >= orderQty[idx])
                    {
                        for (int k = idx; k < orderCount - 1; k++)
                        {           // REMOVE ORDER BY OVERWRITING 
                            orderNames[k] = orderNames[k + 1];
                            orderQty[k] = orderQty[k + 1];
                            orderAmounts[k] = orderAmounts[k + 1];
                        }
                        orderCount--;
                    }
                    else
                    {
                        double unitPrice = orderAmounts[idx] / orderQty[idx];
                        orderQty[idx] -= remQty;
                        orderAmounts[idx] -= (unitPrice * remQty);
                    }
                }
            }
            break;

        case 5:
            return;

        default:
            setColor(12); // FOR RED COLOR
            cout << "Invalid choice.";
            cout << "\nPress any Key to Exit.....";
            setColor(14);
            getch();
            break;
        }
    }
}