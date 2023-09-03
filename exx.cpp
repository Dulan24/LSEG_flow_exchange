#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <string> 
#include <algorithm>

#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>

#include <stdexcept> // Include for exception handling
struct RejectedExecutionReport {
    std::string orderID;
    std::string rejectionReason;
    // You can add more fields if needed
};
bool parseCSVLine(const std::string& line, std::string& ID, std::string& Instrument, int& Side, int& Quantity, double& Price) {
    std::istringstream ss(line);
    std::string field;

    // Attempt to read and convert each field from the line
    if (std::getline(ss, field, ',') && !field.empty()) {
        ID = field;
    } else {
        return false; // ID is missing or empty
    }

    if (std::getline(ss, field, ',') && !field.empty()) {
        Instrument = field;
    } else {
        return false; // Instrument is missing or empty
    }

    if (std::getline(ss, field, ',')) {
        try {
            Side = std::stoi(field);
        } catch (const std::invalid_argument& e) {
            return false; // Invalid Side value
        }
    } else {
        return false; // Side is missing
    }

    if (std::getline(ss, field, ',')) {
        try {
            Quantity = std::stoi(field);
        } catch (const std::invalid_argument& e) {
            return false; // Invalid Quantity value
        }
    } else {
        return false; // Quantity is missing
    }

    if (std::getline(ss, field, ',')) {
        try {
            Price = std::stod(field);
        } catch (const std::invalid_argument& e) {
            return false; // Invalid Price value
        }
    } else {
        return false; // Price is missing
    }

    // Successful parsing and validation
    return true;
}


std::string currentTime() {
    // Get the current time
    auto now = std::chrono::system_clock::now();
    std::time_t currentTime = std::chrono::system_clock::to_time_t(now);

    // Convert the time to a struct tm for formatting
    struct tm timeInfo;
    localtime_s(&timeInfo, &currentTime); // Windows-specific function, use localtime for other platforms

    // Format the timestamp as "YYYYMMDD-HHMMSS.sss"
    std::ostringstream formattedTimestamp;
    formattedTimestamp << std::put_time(&timeInfo, "%Y%m%d-%H%M%S");
    
    // Get milliseconds separately and add to the timestamp
    auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()).count() % 1000;
    formattedTimestamp << "." << std::setw(3) << std::setfill('0') << milliseconds;
    std::string transaction_time=formattedTimestamp.str();
    // Print the timestamp
    // std::cout << "Timestamp: " << formattedTimestamp.str() << std::endl;
    return formattedTimestamp.str();
}

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
    std::vector<Order> roseBuyOrders;
    std::vector<Order> roseSellOrders;
    std::vector<Order> tulipBuyOrders;
    std::vector<Order> tulipSellOrders;
    std::vector<Order> lavenderBuyOrders;
    std::vector<Order> lavenderSellOrders;
    std::vector<Order> lotusBuyOrders;
    std::vector<Order> lotusSellOrders;
    std::vector<Order> orchidBuyOrders;
    std::vector<Order> orchidSellOrders;

    int orderCounter; // Counter for generating order IDs

public:
    Exchange() : orderCounter(0) {} // Initialize the counter to 0
    std::string generateOrderID() {
        return "ord" + std::to_string(++orderCounter);
    }

    void addOrder(const Order& order) {
        if (order.Instrument == "Rose") {
            if (order.Side == 1) {
                // Buy order for Rose
                roseBuyOrders.push_back(order);
                std::sort(roseBuyOrders.begin(), roseBuyOrders.end(), [](const Order& a, const Order& b) {return a.Price < b.Price;});
            } else if (order.Side == 2) {
                // Sell order for Rose
                roseSellOrders.push_back(order);
                std::sort(roseSellOrders.begin(), roseSellOrders.end(), [](const Order& a, const Order& b) {return a.Price > b.Price;});
            }
        }
        if(order.Instrument == "Tulip") {
            if (order.Side == 1) {
                // Buy order for Tulip
                tulipBuyOrders.push_back(order);
                std::sort(tulipBuyOrders.begin(), tulipBuyOrders.end(), [](const Order& a, const Order& b) {return a.Price < b.Price;});
            } else if (order.Side == 2) {
                // Sell order for Tulip
                tulipSellOrders.push_back(order);
                std::sort(tulipSellOrders.begin(), tulipSellOrders.end(), [](const Order& a, const Order& b) {return a.Price > b.Price;});
            }
        }
        if(order.Instrument == "Lavender") {
            if (order.Side == 1) {
                // Buy order for Lavender
                lavenderBuyOrders.push_back(order);
                std::sort(lavenderBuyOrders.begin(), lavenderBuyOrders.end(), [](const Order& a, const Order& b) {return a.Price < b.Price;});
            } else if (order.Side == 2) {
                // Sell order for Lavender
                lavenderSellOrders.push_back(order);
                std::sort(lavenderSellOrders.begin(), lavenderSellOrders.end(), [](const Order& a, const Order& b) {return a.Price > b.Price;});
            }
        }
        if(order.Instrument == "Lotus") {
            if (order.Side == 1) {
                // Buy order for Lotus
                lotusBuyOrders.push_back(order);
                std::sort(lotusBuyOrders.begin(), lotusBuyOrders.end(), [](const Order& a, const Order& b) {return a.Price < b.Price;});
            } else if (order.Side == 2) {
                // Sell order for Lotus
                lotusSellOrders.push_back(order);
                std::sort(lotusSellOrders.begin(), lotusSellOrders.end(), [](const Order& a, const Order& b) {return a.Price > b.Price;});
            }
        }
        if(order.Instrument == "Orchid") {
            if (order.Side == 1) {
                // Buy order for Orchid
                orchidBuyOrders.push_back(order);
                std::sort(orchidBuyOrders.begin(), orchidBuyOrders.end(), [](const Order& a, const Order& b) {return a.Price < b.Price;});
            } else if (order.Side == 2) {
                // Sell order for Orchid
                orchidSellOrders.push_back(order);
                std::sort(orchidSellOrders.begin(), orchidSellOrders.end(), [](const Order& a, const Order& b) {return a.Price > b.Price;});
            }
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

    // creating rejection report
    std::vector<RejectedExecutionReport> rejectionReports;

    // Read and process each line of the input CSV file
    while (std::getline(inputFile, line)) {
        std::istringstream iss(line); 
        std::string ID, Instrument, status;
        int Side, Quantity;
        double Price;

        RejectedExecutionReport rejectionReport;

        //std::cout << "done " << line;
    
        // Create an Order object
        Order order;
        order.Order_ID = exchange.generateOrderID();
        
        order.status = "New";//default status
        //input validation
        //if any of fieds are empy then make the status regected

        if (parseCSVLine(line, ID, Instrument, Side, Quantity, Price)){
            if (ID.empty() || Instrument.empty() || (Side != 1 && Side != 2) ) {
            order.status = "Rejected";
            rejectionReport.rejectionReason = "Invalid Side value";

            }
            else if (Quantity <= 0) {
                order.status = "Rejected";
                rejectionReport.rejectionReason = "Invalid Quantity value";
            }
            else if (Price <= 0.0) {
                order.status = "Rejected";
                rejectionReport.rejectionReason = "Invalid Price value";
            }
            else if (Quantity %10 != 0 || Quantity<10 || Quantity>1000) {
                order.status = "Rejected";
                rejectionReport.rejectionReason = "Invalid Quantity range";
            }
            // if instrument is not any valid instrument then make the status regected
            else if (Instrument != "Rose" && Instrument != "Tulip" && Instrument != "Lavender" && Instrument != "Lotus"&& Instrument != "Orchid") {
                order.status = "Rejected";
                rejectionReport.rejectionReason = "Invalid Instrument";
            }
            else{
                order.status = "New";
            }

            if (order.status=="Rejected"){
                rejectionReports.push_back(rejectionReport);
                // Invalid data in the CSV line, handle the exception or error here
                //std::cerr << "Invalid data in the CSV line: " << line << std::endl;
            }
            else if (order.status=="New"){

                order.Client_Order = ID;
                order.Instrument = Instrument;
                order.Side = Side;
                order.Quantity = Quantity;
                order.Price = Price;
                
                // Valid data, process it here



            }

        } 
        else {
            order.status = "Rejected";
            rejectionReport.rejectionReason = "Invalid order details or missing fields";
            rejectionReports.push_back(rejectionReport);
            // Invalid data in the CSV line, handle the exception or error here
            //std::cerr << "Invalid data in the CSV line: " << line << std::endl;
        }

    }

    // Close the input and output files
    inputFile.close();
    outputFile.close();

    return 0;
}
