#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <string> 

// Define a class for orders
class Order {
public:
    std::string Order_ID;
    std::string Client_Order;
    std::string Instrument;
    int Side;
    int Quantity;
    double Price;
    std::string status;
};

// Define a class for managing orders
class Exchange {
private:
    std::map<std::pair<std::string, int>, std::vector<Order>> instrumentSideOrders;
    int orderCounter; // Counter for generating order IDs

public:
    Exchange() : orderCounter(0) {} // Initialize the counter to 0

    std::string generateOrderID() {
        return "ord" + std::to_string(++orderCounter);
    }

    void addOrder(const std::string& instrument, int side, const Order& order) {
        std::pair<std::string, int> key = std::make_pair(instrument, side);
        instrumentSideOrders[key].push_back(order);
    }

    const std::vector<Order>& getOrders(const std::string& instrument, int side) const {
        std::pair<std::string, int> key = std::make_pair(instrument, side);
        auto it = instrumentSideOrders.find(key);
        if (it != instrumentSideOrders.end()) {
            return it->second;
        } else {
            static const std::vector<Order> emptyVector;
            return emptyVector;
        }
    }
};

int main() {
    // Create an Exchange object
    Exchange exchange;

    // Open and read the input CSV file
    std::ifstream inputFile("input.csv");
    std::ofstream outputFile("output.csv");
    std::string line;

    // Write header to the output CSV file
    outputFile << "order_id,client_ID,Instrument,Side,status,Quantity,Price" << std::endl;

    // Read and process each line of the input CSV file
    while (std::getline(inputFile, line)) {
        std::istringstream iss(line);
        std::string ID, Instrument, status;
        int Side, Quantity;
        double Price;

        // Parse the CSV line to extract relevant data
        if (std::getline(iss, ID, ',') &&
            std::getline(iss, Instrument, ',') &&
            (iss >> Side) &&
            (iss >> Quantity) &&
            (iss >> Price)) {
            // Create an Order object
            Order order;
            order.Order_ID = exchange.generateOrderID();
            order.Client_Order = ID;
            order.Instrument = Instrument;
            order.Side = Side;
            order.Quantity = Quantity;
            order.Price = Price;
            order.status = "New";//default status
            //input validation
            //if any of fieds are empy then make the status regected
           if (ID.empty() || Instrument.empty() || (Side != 1 && Side != 2) || Quantity <= 0 || Price <= 0.0) {
                order.status = "Rejected";
            }
            if (Quantity %10 != 0 || Quantity>10 || Quantity< 1000) {
                order.status = "Rejected";
            }
            // if instrument is not any valid instrument then make the status regected
            if (Instrument != "Rose" && Instrument != "Tulip" && Instrument != "Lavender" && Instrument != "Lotus"&& Instrument != "Orchid") {
                order.status = "Rejected";
            }

            //  before add the vector perform your specific tasks based on instrument and side then change the status,quantity
           


            exchange.addOrder(Instrument, Side, order);

            // Perform your specific tasks based on instrument and side
            // Example: Check rose_sell against rose_buy and modify orders
            if (Instrument == "Rose" && Side == 2) {
                const std::vector<Order>& roseBuyOrders = exchange.getOrders("Rose", 1);
                for (const Order& buyOrder : roseBuyOrders) {
                    if (buyOrder.Price >= Price) {
                        // Perform tasks on matching orders (e.g., change quantity)
                        // Modify the order and update its status as needed
                        // Record the changes to the output CSV file
                        outputFile << buyOrder.ID << "," << ID << "," << Instrument << "," << Side << ","
                                   << "Modified" << "," << buyOrder.Quantity << "," << buyOrder.Price << std::endl;
                    }
                }
            }
        }
    }

    // Close the input and output files
    inputFile.close();
    outputFile.close();

    return 0;
}
