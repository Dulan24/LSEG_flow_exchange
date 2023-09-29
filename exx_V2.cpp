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
    std::string transactiontime;
};


void printorderbook(const std::vector<Order>& orders) {
    for (const Order& order : orders) {
        std::cout << "Order ID: " << order.Order_ID << ", ";
        std::cout << "Client Order: " << order.Client_Order << ", ";
        std::cout << "Instrument: " << order.Instrument << ", ";
        std::cout << "Side: " << order.Side << ", ";
        std::cout << "Quantity: " << order.Quantity << ", ";
        std::cout << "Price: " << order.Price << ", ";
        std::cout << "Status: " << order.status <<  std::endl;
        
    }
    std::cout << "done" << std::endl;
}

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
                std::sort(roseBuyOrders.begin(), roseBuyOrders.end(), [](const Order& a, const Order& b) {if (a.Price == b.Price) {return a.Order_ID < b.Order_ID;} return a.Price < b.Price;});
            } else if (order.Side == 2) {
                // Sell order for Rose
                roseSellOrders.push_back(order);
                std::sort(roseSellOrders.begin(), roseSellOrders.end(), [](const Order& a, const Order& b) {if (a.Price == b.Price) {return a.Order_ID > b.Order_ID;} return a.Price > b.Price;});
            }
        }
        if(order.Instrument == "Tulip") {
            if (order.Side == 1) {
                // Buy order for Tulip
                tulipBuyOrders.push_back(order);
                std::sort(tulipBuyOrders.begin(), tulipBuyOrders.end(), [](const Order& a, const Order& b) {if (a.Price == b.Price) {return a.Order_ID < b.Order_ID;} return a.Price < b.Price;});
            } else if (order.Side == 2) {
                // Sell order for Tulip
                tulipSellOrders.push_back(order);
                std::sort(tulipSellOrders.begin(), tulipSellOrders.end(), [](const Order& a, const Order& b) {if (a.Price == b.Price) {return a.Order_ID > b.Order_ID;} return a.Price > b.Price;});
            }
        }
        if(order.Instrument == "Lavender") {
            if (order.Side == 1) {
                // Buy order for Lavender
                lavenderBuyOrders.push_back(order);
                std::sort(lavenderBuyOrders.begin(), lavenderBuyOrders.end(), [](const Order& a, const Order& b) {if (a.Price == b.Price) {return a.Order_ID < b.Order_ID;} return a.Price < b.Price;});
            } else if (order.Side == 2) {
                // Sell order for Lavender
                lavenderSellOrders.push_back(order);
                std::sort(lavenderSellOrders.begin(), lavenderSellOrders.end(), [](const Order& a, const Order& b) {if (a.Price == b.Price) {return a.Order_ID > b.Order_ID;} return a.Price > b.Price;});
            }
        }
        if(order.Instrument == "Lotus") {
            if (order.Side == 1) {
                // Buy order for Lotus
                lotusBuyOrders.push_back(order);
                std::sort(lotusBuyOrders.begin(), lotusBuyOrders.end(), [](const Order& a, const Order& b) {if (a.Price == b.Price) {return a.Order_ID < b.Order_ID;} return a.Price < b.Price;});
            } else if (order.Side == 2) {
                // Sell order for Lotus
                lotusSellOrders.push_back(order);
                std::sort(lotusSellOrders.begin(), lotusSellOrders.end(), [](const Order& a, const Order& b) {if (a.Price == b.Price) {return a.Order_ID > b.Order_ID;} return a.Price > b.Price;});
            }
        }
        if(order.Instrument == "Orchid") {
            if (order.Side == 1) {
                // Buy order for Orchid
                orchidBuyOrders.push_back(order);
                std::sort(orchidBuyOrders.begin(), orchidBuyOrders.end(), [](const Order& a, const Order& b) {if (a.Price == b.Price) {return a.Order_ID < b.Order_ID;} return a.Price < b.Price;});
            } else if (order.Side == 2) {
                // Sell order for Orchid
                orchidSellOrders.push_back(order);
                std::sort(orchidSellOrders.begin(), orchidSellOrders.end(), [](const Order& a, const Order& b) {if (a.Price == b.Price) {return a.Order_ID > b.Order_ID;} return a.Price > b.Price;});
            }
        }
    }

    std::vector<Order>& getRoseBuyOrders() {
        return roseBuyOrders;
    }

    std::vector<Order>& getRoseSellOrders() {
        return roseSellOrders;
    }
    std::vector<Order>& getTulipBuyOrders() {
        return tulipBuyOrders;
    }
    std::vector<Order>& getTulipSellOrders() {
        return tulipSellOrders;
    }
    std::vector<Order>& getLavenderBuyOrders() {
        return lavenderBuyOrders;
    }   
    std::vector<Order>& getLavenderSellOrders() {
        return lavenderSellOrders;
    }
    std::vector<Order>& getLotusBuyOrders() {
        return lotusBuyOrders;
    }
    std::vector<Order>& getLotusSellOrders() {
        return lotusSellOrders;
    }
    std::vector<Order>& getOrchidBuyOrders() {
        return orchidBuyOrders;
    }
    std::vector<Order>& getOrchidSellOrders() {
        return orchidSellOrders;
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
                //order.transactiontime = 
                
                // Valid data, process it here
                // size_t roseSellOrdersSize = exchange.getRoseSellOrders().size();
                // size_t roseBuyOrdersSize = exchange.getRoseBuyOrders().size();
                // size_t tulipSellOrdersSize = exchange.getTulipSellOrders().size();
                // size_t tulipBuyOrdersSize = exchange.getTulipBuyOrders().size();
                // size_t lavenderSellOrdersSize = exchange.getLavenderSellOrders().size();
                // size_t lavenderBuyOrdersSize = exchange.getLavenderBuyOrders().size();
                // size_t lotusSellOrdersSize = exchange.getLotusSellOrders().size();
                // size_t lotusBuyOrdersSize = exchange.getLotusBuyOrders().size();
                // size_t orchidSellOrdersSize = exchange.getOrchidSellOrders().size();
                // size_t orchidBuyOrdersSize = exchange.getOrchidBuyOrders().size();
                std::stringstream output;
                // for rose
                if(order.Instrument=="Rose"){
                    if(order.Side==1){   //1=Buy, 2=Sell
                        
                        if(exchange.getRoseSellOrders().size() == 0){
                            exchange.addOrder(order);
                            order.status = "New";
                            output << order.Order_ID << "," << order.Client_Order << "," << order.Instrument << "," << order.Side << "," << order.status << "," << order.Quantity << "," << order.Price;
                            outputFile << output.str() << std::endl;
                            printorderbook(exchange.getRoseBuyOrders());
                        }
                        else{ // sell contains elements
                            while(exchange.getRoseSellOrders().back().Price <= order.Price){
                                // prices matches
                                if(exchange.getRoseSellOrders().back().Quantity==order.Quantity){// quantity matches
                                    //remove the sell order
                                    Order sold = exchange.getRoseSellOrders().back();
                                    exchange.getRoseSellOrders().pop_back();
                                    
                                    //record to output of buy
                                    order.status = "Fill";
                                    output << order.Order_ID << "," << order.Client_Order << "," << order.Instrument << "," << order.Side << "," << order.status << "," << order.Quantity << "," << sold.Price;
                                    outputFile << output.str() << std::endl;

                                    //recordd to output of sell
                                    sold.status = "Fill";
                                    output.str("");
                                    output << sold.Order_ID << "," << sold.Client_Order << "," << sold.Instrument << "," << sold.Side << "," << sold.status << "," << order.Quantity << "," << sold.Price;
                                    outputFile << output.str() << std::endl;
                                    break;
                                }

                                else if(exchange.getRoseSellOrders().back().Quantity > order.Quantity){
                                    //remove the sell order
                                    Order sold = exchange.getRoseSellOrders().back();
                                    exchange.getRoseSellOrders().pop_back();
                                    // can only buy at sell order price
                                    order.Price = sold.Price;
                                    
                                    //record to output of buy
                                    order.status = "Fill";
                                    output.str("");
                                    output << order.Order_ID << "," << order.Client_Order << "," << order.Instrument << "," << order.Side << "," << order.status << "," << order.Quantity << "," << sold.Price;
                                    outputFile << output.str() << std::endl;

                                    //change the quantity
                                    exchange.getRoseSellOrders().back().Quantity = exchange.getRoseSellOrders().back().Quantity - order.Quantity;

                                    //record to output of sell
                                    sold.status = "PFill";
                                    output.str("");
                                    output << sold.Order_ID << "," << sold.Client_Order << "," << sold.Instrument << "," << sold.Side << "," << sold.status << "," << order.Quantity << "," << sold.Price;
                                    outputFile << output.str() << std::endl;
                                }

                                else{ // selling quantity is less than the buying quantity
                                    int buyingQuantity = order.Quantity;
                                    
                                    //remove the sell order
                                    Order sold = exchange.getRoseSellOrders().back();
                                    exchange.getRoseSellOrders().pop_back();

                                    //recordd to output of sell
                                    sold.status = "Fill";
                                    output.str("");
                                    output << sold.Order_ID << "," << sold.Client_Order << "," << sold.Instrument << "," << sold.Side << "," << sold.status << "," << sold.Quantity << "," << sold.Price;
                                    outputFile << output.str() << std::endl;

                                    //record to output of buy
                                    order.status = "PFill";
                                    order.Quantity = order.Quantity - sold.Quantity;
                                    output.str("");
                                    output << order.Order_ID << "," << order.Client_Order << "," << order.Instrument << "," << order.Side << "," << order.status << "," << sold.Quantity << "," << sold.Price;
                                    outputFile << output.str() << std::endl;
                                }
                            }
                        }
                    }
                    else if (order.Side==2){ // sell
                        if(exchange.getRoseBuyOrders().size() == 0){ // no buy orders in the book
                            exchange.addOrder(order);
                            order.status = "New";
                            output << order.Order_ID << "," << order.Client_Order << "," << order.Instrument << "," << order.Side << "," << order.status << "," << order.Quantity << "," << order.Price;
                            outputFile << output.str() << std::endl;
                        }
                        else{ // there are buy orders in the book
                            while (exchange.getRoseBuyOrders().back().Price >= order.Price){ // price matches
                                if (exchange.getRoseBuyOrders().back().Quantity == order.Quantity){ // quantity matches
                                    // remove the buy order
                                    Order sold = exchange.getRoseBuyOrders().back();
                                    exchange.getRoseBuyOrders().pop_back();

                                    // record the output of sell
                                    order.status = "Fill";
                                    output.str("");
                                    output << order.Order_ID << "," << order.Client_Order << "," << order.Instrument << "," << order.Side << "," << order.status << "," << order.Quantity << "," << sold.Price;
                                    outputFile << output.str() << std::endl;

                                    // record the output of buy
                                    sold.status = "Fill";
                                    output.str("");
                                    output << sold.Order_ID << "," << sold.Client_Order << "," << sold.Instrument << "," << sold.Side << "," << sold.status << "," << order.Quantity << "," << sold.Price;
                                    outputFile << output.str() << std::endl;
                                    break; 
                                }
                                else if (exchange.getRoseBuyOrders().back().Quantity > order.Quantity){ 
                                    // record the output of buy
                                    Order sold = exchange.getRoseBuyOrders().back();
                                    sold.status = "PFill";
                                    output.str("");
                                    output << sold.Order_ID << "," << sold.Client_Order << "," << sold.Instrument << "," << sold.Side << "," << sold.status << "," << order.Quantity << "," << sold.Price;
                                    outputFile << output.str() << std::endl;
                                    
                                    // record the output of sell order
                                    order.status = "Fill";
                                    output.str("");
                                    output << order.Order_ID << "," << order.Client_Order << "," << order.Instrument << "," << order.Side << "," << order.status << "," << order.Quantity << "," << sold.Price;
                                    outputFile << output.str() << std::endl;

                                    // change the quantity
                                    exchange.getRoseBuyOrders().back().Quantity = exchange.getRoseBuyOrders().back().Quantity - order.Quantity;
                                    
                                }
                                else { // selling quantity is higher than buying quantity

                                    // remove the buy order
                                    Order sold = exchange.getRoseBuyOrders().back();
                                    exchange.getRoseBuyOrders().pop_back();
                                    
                                    // record the output of buy
                                    sold.status = "Fill";
                                    output.str("");
                                    output << sold.Order_ID << "," << sold.Client_Order << "," << sold.Instrument << "," << sold.Side << "," << sold.status << "," << sold.Quantity << "," << sold.Price;
                                    outputFile << output.str() << std::endl;

                                    // record the output of sell
                                    order.status = "PFill";
                                    order.Quantity = order.Quantity - sold.Quantity;
                                    output.str("");
                                    output << order.Order_ID << "," << order.Client_Order << "," << order.Instrument << "," << order.Side << "," << order.status << "," << sold.Quantity << "," << sold.Price;
                                    outputFile << output.str() << std::endl;
                                }
                                
                            }
                        }
                    }
                }

                //for Tulip
                else if(order.Instrument=="Tulip"){
                    if(order.Side==1){   //1=Buy, 2=Sell
                        
                        if(exchange.getTulipSellOrders().size() == 0){
                            exchange.addOrder(order);
                            order.status = "New";
                            output << order.Order_ID << "," << order.Client_Order << "," << order.Instrument << "," << order.Side << "," << order.status << "," << order.Quantity << "," << order.Price;
                            outputFile << output.str() << std::endl;
                            printorderbook(exchange.getTulipBuyOrders());
                        }
                        else{ // sell contains elements
                            while(exchange.getTulipSellOrders().back().Price <= order.Price){
                                // prices matches
                                if(exchange.getTulipSellOrders().back().Quantity==order.Quantity){// quantity matches
                                    //remove the sell order
                                    Order sold = exchange.getTulipSellOrders().back();
                                    exchange.getTulipSellOrders().pop_back();
                                    
                                    //record to output of buy
                                    order.status = "Fill";
                                    output << order.Order_ID << "," << order.Client_Order << "," << order.Instrument << "," << order.Side << "," << order.status << "," << order.Quantity << "," << sold.Price;
                                    outputFile << output.str() << std::endl;

                                    //recordd to output of sell
                                    sold.status = "Fill";
                                    output.str("");
                                    output << sold.Order_ID << "," << sold.Client_Order << "," << sold.Instrument << "," << sold.Side << "," << sold.status << "," << order.Quantity << "," << sold.Price;
                                    outputFile << output.str() << std::endl;
                                    break;
                                }

                                else if(exchange.getTulipSellOrders().back().Quantity > order.Quantity){
                                    //remove the sell order
                                    Order sold = exchange.getTulipSellOrders().back();
                                    exchange.getTulipSellOrders().pop_back();
                                    // can only buy at sell order price
                                    order.Price = sold.Price;
                                    
                                    //record to output of buy
                                    order.status = "Fill";
                                    output.str("");
                                    output << order.Order_ID << "," << order.Client_Order << "," << order.Instrument << "," << order.Side << "," << order.status << "," << order.Quantity << "," << sold.Price;
                                    outputFile << output.str() << std::endl;

                                    //change the quantity
                                    exchange.getTulipSellOrders().back().Quantity = exchange.getTulipSellOrders().back().Quantity - order.Quantity;

                                    //record to output of sell
                                    sold.status = "PFill";
                                    output.str("");
                                    output << sold.Order_ID << "," << sold.Client_Order << "," << sold.Instrument << "," << sold.Side << "," << sold.status << "," << order.Quantity << "," << sold.Price;
                                    outputFile << output.str() << std::endl;
                                }

                                else{ // selling quantity is less than the buying quantity
                                    int buyingQuantity = order.Quantity;
                                    
                                    //remove the sell order
                                    Order sold = exchange.getTulipSellOrders().back();
                                    exchange.getTulipSellOrders().pop_back();

                                    //recordd to output of sell
                                    sold.status = "Fill";
                                    output.str("");
                                    output << sold.Order_ID << "," << sold.Client_Order << "," << sold.Instrument << "," << sold.Side << "," << sold.status << "," << sold.Quantity << "," << sold.Price;
                                    outputFile << output.str() << std::endl;

                                    //record to output of buy
                                    order.status = "PFill";
                                    order.Quantity = order.Quantity - sold.Quantity;
                                    output.str("");
                                    output << order.Order_ID << "," << order.Client_Order << "," << order.Instrument << "," << order.Side << "," << order.status << "," << sold.Quantity << "," << sold.Price;
                                    outputFile << output.str() << std::endl;
                                }
                            }
                        }
                    }
                    else if (order.Side==2){ // sell
                        if(exchange.getTulipBuyOrders().size() == 0){ // no buy orders in the book
                            exchange.addOrder(order);
                            order.status = "New";
                            output << order.Order_ID << "," << order.Client_Order << "," << order.Instrument << "," << order.Side << "," << order.status << "," << order.Quantity << "," << order.Price;
                            outputFile << output.str() << std::endl;
                        }
                        else{ // there are buy orders in the book
                            while (exchange.getTulipBuyOrders().back().Price >= order.Price){ // price matches
                                if (exchange.getTulipBuyOrders().back().Quantity == order.Quantity){ // quantity matches
                                    // remove the buy order
                                    Order sold = exchange.getTulipBuyOrders().back();
                                    exchange.getTulipBuyOrders().pop_back();

                                    // record the output of sell
                                    order.status = "Fill";
                                    output.str("");
                                    output << order.Order_ID << "," << order.Client_Order << "," << order.Instrument << "," << order.Side << "," << order.status << "," << order.Quantity << "," << sold.Price;
                                    outputFile << output.str() << std::endl;

                                    // record the output of buy
                                    sold.status = "Fill";
                                    output.str("");
                                    output << sold.Order_ID << "," << sold.Client_Order << "," << sold.Instrument << "," << sold.Side << "," << sold.status << "," << order.Quantity << "," << sold.Price;
                                    outputFile << output.str() << std::endl;
                                    break; 
                                }
                                else if (exchange.getTulipBuyOrders().back().Quantity > order.Quantity){ 
                                    // record the output of buy
                                    Order sold = exchange.getTulipBuyOrders().back();
                                    sold.status = "PFill";
                                    output.str("");
                                    output << sold.Order_ID << "," << sold.Client_Order << "," << sold.Instrument << "," << sold.Side << "," << sold.status << "," << order.Quantity << "," << sold.Price;
                                    outputFile << output.str() << std::endl;
                                    
                                    // record the output of sell order
                                    order.status = "Fill";
                                    output.str("");
                                    output << order.Order_ID << "," << order.Client_Order << "," << order.Instrument << "," << order.Side << "," << order.status << "," << order.Quantity << "," << sold.Price;
                                    outputFile << output.str() << std::endl;

                                    // change the quantity
                                    exchange.getTulipBuyOrders().back().Quantity = exchange.getTulipBuyOrders().back().Quantity - order.Quantity;
                                    
                                }
                                else { // selling quantity is higher than buying quantity

                                    // remove the buy order
                                    Order sold = exchange.getTulipBuyOrders().back();
                                    exchange.getTulipBuyOrders().pop_back();
                                    
                                    // record the output of buy
                                    sold.status = "Fill";
                                    output.str("");
                                    output << sold.Order_ID << "," << sold.Client_Order << "," << sold.Instrument << "," << sold.Side << "," << sold.status << "," << sold.Quantity << "," << sold.Price;
                                    outputFile << output.str() << std::endl;

                                    // record the output of sell
                                    order.status = "PFill";
                                    order.Quantity = order.Quantity - sold.Quantity;
                                    output.str("");
                                    output << order.Order_ID << "," << order.Client_Order << "," << order.Instrument << "," << order.Side << "," << order.status << "," << sold.Quantity << "," << sold.Price;
                                    outputFile << output.str() << std::endl;
                                }
                                
                            }
                        }
                    }
                }

                //for Lavender
                else if(order.Instrument=="Lavender"){
                    if(order.Side==1){   //1=Buy, 2=Sell
                        
                        if(exchange.getLavenderSellOrders().size() == 0){
                            exchange.addOrder(order);
                            order.status = "New";
                            output << order.Order_ID << "," << order.Client_Order << "," << order.Instrument << "," << order.Side << "," << order.status << "," << order.Quantity << "," << order.Price;
                            outputFile << output.str() << std::endl;
                            printorderbook(exchange.getLavenderBuyOrders());
                        }
                        else{ // sell contains elements
                            while(exchange.getLavenderSellOrders().back().Price <= order.Price){
                                // prices matches
                                if(exchange.getLavenderSellOrders().back().Quantity==order.Quantity){// quantity matches
                                    //remove the sell order
                                    Order sold = exchange.getLavenderSellOrders().back();
                                    exchange.getLavenderSellOrders().pop_back();
                                    
                                    //record to output of buy
                                    order.status = "Fill";
                                    output << order.Order_ID << "," << order.Client_Order << "," << order.Instrument << "," << order.Side << "," << order.status << "," << order.Quantity << "," << sold.Price;
                                    outputFile << output.str() << std::endl;

                                    //recordd to output of sell
                                    sold.status = "Fill";
                                    output.str("");
                                    output << sold.Order_ID << "," << sold.Client_Order << "," << sold.Instrument << "," << sold.Side << "," << sold.status << "," << order.Quantity << "," << sold.Price;
                                    outputFile << output.str() << std::endl;
                                    break;
                                }

                                else if(exchange.getLavenderSellOrders().back().Quantity > order.Quantity){
                                    //remove the sell order
                                    Order sold = exchange.getLavenderSellOrders().back();
                                    exchange.getLavenderSellOrders().pop_back();
                                    // can only buy at sell order price
                                    order.Price = sold.Price;
                                    
                                    //record to output of buy
                                    order.status = "Fill";
                                    output.str("");
                                    output << order.Order_ID << "," << order.Client_Order << "," << order.Instrument << "," << order.Side << "," << order.status << "," << order.Quantity << "," << sold.Price;
                                    outputFile << output.str() << std::endl;

                                    //change the quantity
                                    exchange.getLavenderSellOrders().back().Quantity = exchange.getLavenderSellOrders().back().Quantity - order.Quantity;

                                    //record to output of sell
                                    sold.status = "PFill";
                                    output.str("");
                                    output << sold.Order_ID << "," << sold.Client_Order << "," << sold.Instrument << "," << sold.Side << "," << sold.status << "," << order.Quantity << "," << sold.Price;
                                    outputFile << output.str() << std::endl;
                                }

                                else{ // selling quantity is less than the buying quantity
                                    int buyingQuantity = order.Quantity;
                                    
                                    //remove the sell order
                                    Order sold = exchange.getLavenderSellOrders().back();
                                    exchange.getLavenderSellOrders().pop_back();

                                    //recordd to output of sell
                                    sold.status = "Fill";
                                    output.str("");
                                    output << sold.Order_ID << "," << sold.Client_Order << "," << sold.Instrument << "," << sold.Side << "," << sold.status << "," << sold.Quantity << "," << sold.Price;
                                    outputFile << output.str() << std::endl;

                                    //record to output of buy
                                    order.status = "PFill";
                                    order.Quantity = order.Quantity - sold.Quantity;
                                    output.str("");
                                    output << order.Order_ID << "," << order.Client_Order << "," << order.Instrument << "," << order.Side << "," << order.status << "," << sold.Quantity << "," << sold.Price;
                                    outputFile << output.str() << std::endl;
                                }
                            }
                        }
                    }
                    else if (order.Side==2){ // sell
                        if(exchange.getLavenderBuyOrders().size() == 0){ // no buy orders in the book
                            exchange.addOrder(order);
                            order.status = "New";
                            output << order.Order_ID << "," << order.Client_Order << "," << order.Instrument << "," << order.Side << "," << order.status << "," << order.Quantity << "," << order.Price;
                            outputFile << output.str() << std::endl;
                        }
                        else{ // there are buy orders in the book
                            while (exchange.getLavenderBuyOrders().back().Price >= order.Price){ // price matches
                                if (exchange.getLavenderBuyOrders().back().Quantity == order.Quantity){ // quantity matches
                                    // remove the buy order
                                    Order sold = exchange.getLavenderBuyOrders().back();
                                    exchange.getLavenderBuyOrders().pop_back();

                                    // record the output of sell
                                    order.status = "Fill";
                                    output.str("");
                                    output << order.Order_ID << "," << order.Client_Order << "," << order.Instrument << "," << order.Side << "," << order.status << "," << order.Quantity << "," << sold.Price;
                                    outputFile << output.str() << std::endl;

                                    // record the output of buy
                                    sold.status = "Fill";
                                    output.str("");
                                    output << sold.Order_ID << "," << sold.Client_Order << "," << sold.Instrument << "," << sold.Side << "," << sold.status << "," << order.Quantity << "," << sold.Price;
                                    outputFile << output.str() << std::endl;
                                    break; 
                                }
                                else if (exchange.getLavenderBuyOrders().back().Quantity > order.Quantity){ 
                                    // record the output of buy
                                    Order sold = exchange.getLavenderBuyOrders().back();
                                    sold.status = "PFill";
                                    output.str("");
                                    output << sold.Order_ID << "," << sold.Client_Order << "," << sold.Instrument << "," << sold.Side << "," << sold.status << "," << order.Quantity << "," << sold.Price;
                                    outputFile << output.str() << std::endl;
                                    
                                    // record the output of sell order
                                    order.status = "Fill";
                                    output.str("");
                                    output << order.Order_ID << "," << order.Client_Order << "," << order.Instrument << "," << order.Side << "," << order.status << "," << order.Quantity << "," << sold.Price;
                                    outputFile << output.str() << std::endl;

                                    // change the quantity
                                    exchange.getLavenderBuyOrders().back().Quantity = exchange.getLavenderBuyOrders().back().Quantity - order.Quantity;
                                    
                                }
                                else { // selling quantity is higher than buying quantity

                                    // remove the buy order
                                    Order sold = exchange.getLavenderBuyOrders().back();
                                    exchange.getLavenderBuyOrders().pop_back();
                                    
                                    // record the output of buy
                                    sold.status = "Fill";
                                    output.str("");
                                    output << sold.Order_ID << "," << sold.Client_Order << "," << sold.Instrument << "," << sold.Side << "," << sold.status << "," << sold.Quantity << "," << sold.Price;
                                    outputFile << output.str() << std::endl;

                                    // record the output of sell
                                    order.status = "PFill";
                                    order.Quantity = order.Quantity - sold.Quantity;
                                    output.str("");
                                    output << order.Order_ID << "," << order.Client_Order << "," << order.Instrument << "," << order.Side << "," << order.status << "," << sold.Quantity << "," << sold.Price;
                                    outputFile << output.str() << std::endl;
                                }
                                
                            }
                        }
                    }
                }

                //for Lotus
                else if(order.Instrument=="Lotus"){
                    if(order.Side==1){   //1=Buy, 2=Sell
                        
                        if(exchange.getLotusSellOrders().size() == 0){
                            exchange.addOrder(order);
                            order.status = "New";
                            output << order.Order_ID << "," << order.Client_Order << "," << order.Instrument << "," << order.Side << "," << order.status << "," << order.Quantity << "," << order.Price;
                            outputFile << output.str() << std::endl;
                            printorderbook(exchange.getLotusBuyOrders());
                        }
                        else{ // sell contains elements
                            while(exchange.getLotusSellOrders().back().Price <= order.Price){
                                // prices matches
                                if(exchange.getLotusSellOrders().back().Quantity==order.Quantity){// quantity matches
                                    //remove the sell order
                                    Order sold = exchange.getLotusSellOrders().back();
                                    exchange.getLotusSellOrders().pop_back();
                                    
                                    //record to output of buy
                                    order.status = "Fill";
                                    output << order.Order_ID << "," << order.Client_Order << "," << order.Instrument << "," << order.Side << "," << order.status << "," << order.Quantity << "," << sold.Price;
                                    outputFile << output.str() << std::endl;

                                    //recordd to output of sell
                                    sold.status = "Fill";
                                    output.str("");
                                    output << sold.Order_ID << "," << sold.Client_Order << "," << sold.Instrument << "," << sold.Side << "," << sold.status << "," << order.Quantity << "," << sold.Price;
                                    outputFile << output.str() << std::endl;
                                    break;
                                }

                                else if(exchange.getLotusSellOrders().back().Quantity > order.Quantity){
                                    //remove the sell order
                                    Order sold = exchange.getLotusSellOrders().back();
                                    exchange.getLotusSellOrders().pop_back();
                                    // can only buy at sell order price
                                    order.Price = sold.Price;
                                    
                                    //record to output of buy
                                    order.status = "Fill";
                                    output.str("");
                                    output << order.Order_ID << "," << order.Client_Order << "," << order.Instrument << "," << order.Side << "," << order.status << "," << order.Quantity << "," << sold.Price;
                                    outputFile << output.str() << std::endl;

                                    //change the quantity
                                    exchange.getLotusSellOrders().back().Quantity = exchange.getLotusSellOrders().back().Quantity - order.Quantity;

                                    //record to output of sell
                                    sold.status = "PFill";
                                    output.str("");
                                    output << sold.Order_ID << "," << sold.Client_Order << "," << sold.Instrument << "," << sold.Side << "," << sold.status << "," << order.Quantity << "," << sold.Price;
                                    outputFile << output.str() << std::endl;
                                }

                                else{ // selling quantity is less than the buying quantity
                                    int buyingQuantity = order.Quantity;
                                    
                                    //remove the sell order
                                    Order sold = exchange.getLotusSellOrders().back();
                                    exchange.getLotusSellOrders().pop_back();

                                    //recordd to output of sell
                                    sold.status = "Fill";
                                    output.str("");
                                    output << sold.Order_ID << "," << sold.Client_Order << "," << sold.Instrument << "," << sold.Side << "," << sold.status << "," << sold.Quantity << "," << sold.Price;
                                    outputFile << output.str() << std::endl;

                                    //record to output of buy
                                    order.status = "PFill";
                                    order.Quantity = order.Quantity - sold.Quantity;
                                    output.str("");
                                    output << order.Order_ID << "," << order.Client_Order << "," << order.Instrument << "," << order.Side << "," << order.status << "," << sold.Quantity << "," << sold.Price;
                                    outputFile << output.str() << std::endl;
                                }
                            }
                        }
                    }
                    else if (order.Side==2){ // sell
                        if(exchange.getLotusBuyOrders().size() == 0){ // no buy orders in the book
                            exchange.addOrder(order);
                            order.status = "New";
                            output << order.Order_ID << "," << order.Client_Order << "," << order.Instrument << "," << order.Side << "," << order.status << "," << order.Quantity << "," << order.Price;
                            outputFile << output.str() << std::endl;
                        }
                        else{ // there are buy orders in the book
                            while (exchange.getLotusBuyOrders().back().Price >= order.Price){ // price matches
                                if (exchange.getLotusBuyOrders().back().Quantity == order.Quantity){ // quantity matches
                                    // remove the buy order
                                    Order sold = exchange.getLotusBuyOrders().back();
                                    exchange.getLotusBuyOrders().pop_back();

                                    // record the output of sell
                                    order.status = "Fill";
                                    output.str("");
                                    output << order.Order_ID << "," << order.Client_Order << "," << order.Instrument << "," << order.Side << "," << order.status << "," << order.Quantity << "," << sold.Price;
                                    outputFile << output.str() << std::endl;

                                    // record the output of buy
                                    sold.status = "Fill";
                                    output.str("");
                                    output << sold.Order_ID << "," << sold.Client_Order << "," << sold.Instrument << "," << sold.Side << "," << sold.status << "," << order.Quantity << "," << sold.Price;
                                    outputFile << output.str() << std::endl;
                                    break; 
                                }
                                else if (exchange.getLotusBuyOrders().back().Quantity > order.Quantity){ 
                                    // record the output of buy
                                    Order sold = exchange.getLotusBuyOrders().back();
                                    sold.status = "PFill";
                                    output.str("");
                                    output << sold.Order_ID << "," << sold.Client_Order << "," << sold.Instrument << "," << sold.Side << "," << sold.status << "," << order.Quantity << "," << sold.Price;
                                    outputFile << output.str() << std::endl;
                                    
                                    // record the output of sell order
                                    order.status = "Fill";
                                    output.str("");
                                    output << order.Order_ID << "," << order.Client_Order << "," << order.Instrument << "," << order.Side << "," << order.status << "," << order.Quantity << "," << sold.Price;
                                    outputFile << output.str() << std::endl;

                                    // change the quantity
                                    exchange.getLotusBuyOrders().back().Quantity = exchange.getLotusBuyOrders().back().Quantity - order.Quantity;
                                    
                                }
                                else { // selling quantity is higher than buying quantity

                                    // remove the buy order
                                    Order sold = exchange.getLotusBuyOrders().back();
                                    exchange.getLotusBuyOrders().pop_back();
                                    
                                    // record the output of buy
                                    sold.status = "Fill";
                                    output.str("");
                                    output << sold.Order_ID << "," << sold.Client_Order << "," << sold.Instrument << "," << sold.Side << "," << sold.status << "," << sold.Quantity << "," << sold.Price;
                                    outputFile << output.str() << std::endl;

                                    // record the output of sell
                                    order.status = "PFill";
                                    order.Quantity = order.Quantity - sold.Quantity;
                                    output.str("");
                                    output << order.Order_ID << "," << order.Client_Order << "," << order.Instrument << "," << order.Side << "," << order.status << "," << sold.Quantity << "," << sold.Price;
                                    outputFile << output.str() << std::endl;
                                }
                                
                            }
                        }
                    }
                }

                //for Orchid
                else if(order.Instrument=="Orchid"){
                    if(order.Side==1){   //1=Buy, 2=Sell
                        
                        if(exchange.getOrchidSellOrders().size() == 0){
                            exchange.addOrder(order);
                            order.status = "New";
                            output << order.Order_ID << "," << order.Client_Order << "," << order.Instrument << "," << order.Side << "," << order.status << "," << order.Quantity << "," << order.Price;
                            outputFile << output.str() << std::endl;
                            printorderbook(exchange.getOrchidBuyOrders());
                        }
                        else{ // sell contains elements
                            while(exchange.getOrchidSellOrders().back().Price <= order.Price){
                                // prices matches
                                if(exchange.getOrchidSellOrders().back().Quantity==order.Quantity){// quantity matches
                                    //remove the sell order
                                    Order sold = exchange.getOrchidSellOrders().back();
                                    exchange.getOrchidSellOrders().pop_back();
                                    
                                    //record to output of buy
                                    order.status = "Fill";
                                    output << order.Order_ID << "," << order.Client_Order << "," << order.Instrument << "," << order.Side << "," << order.status << "," << order.Quantity << "," << sold.Price;
                                    outputFile << output.str() << std::endl;

                                    //recordd to output of sell
                                    sold.status = "Fill";
                                    output.str("");
                                    output << sold.Order_ID << "," << sold.Client_Order << "," << sold.Instrument << "," << sold.Side << "," << sold.status << "," << order.Quantity << "," << sold.Price;
                                    outputFile << output.str() << std::endl;
                                    break;
                                }

                                else if(exchange.getOrchidSellOrders().back().Quantity > order.Quantity){
                                    //remove the sell order
                                    Order sold = exchange.getOrchidSellOrders().back();
                                    exchange.getOrchidSellOrders().pop_back();
                                    // can only buy at sell order price
                                    order.Price = sold.Price;
                                    
                                    //record to output of buy
                                    order.status = "Fill";
                                    output.str("");
                                    output << order.Order_ID << "," << order.Client_Order << "," << order.Instrument << "," << order.Side << "," << order.status << "," << order.Quantity << "," << sold.Price;
                                    outputFile << output.str() << std::endl;

                                    //change the quantity
                                    exchange.getOrchidSellOrders().back().Quantity = exchange.getOrchidSellOrders().back().Quantity - order.Quantity;

                                    //record to output of sell
                                    sold.status = "PFill";
                                    output.str("");
                                    output << sold.Order_ID << "," << sold.Client_Order << "," << sold.Instrument << "," << sold.Side << "," << sold.status << "," << order.Quantity << "," << sold.Price;
                                    outputFile << output.str() << std::endl;
                                }

                                else{ // selling quantity is less than the buying quantity
                                    int buyingQuantity = order.Quantity;
                                    
                                    //remove the sell order
                                    Order sold = exchange.getOrchidSellOrders().back();
                                    exchange.getOrchidSellOrders().pop_back();

                                    //recordd to output of sell
                                    sold.status = "Fill";
                                    output.str("");
                                    output << sold.Order_ID << "," << sold.Client_Order << "," << sold.Instrument << "," << sold.Side << "," << sold.status << "," << sold.Quantity << "," << sold.Price;
                                    outputFile << output.str() << std::endl;

                                    //record to output of buy
                                    order.status = "PFill";
                                    order.Quantity = order.Quantity - sold.Quantity;
                                    output.str("");
                                    output << order.Order_ID << "," << order.Client_Order << "," << order.Instrument << "," << order.Side << "," << order.status << "," << sold.Quantity << "," << sold.Price;
                                    outputFile << output.str() << std::endl;
                                }
                            }
                        }
                    }
                    else if (order.Side==2){ // sell
                        if(exchange.getOrchidBuyOrders().size() == 0){ // no buy orders in the book
                            exchange.addOrder(order);
                            order.status = "New";
                            output << order.Order_ID << "," << order.Client_Order << "," << order.Instrument << "," << order.Side << "," << order.status << "," << order.Quantity << "," << order.Price;
                            outputFile << output.str() << std::endl;
                        }
                        else{ // there are buy orders in the book
                            while (exchange.getOrchidBuyOrders().back().Price >= order.Price){ // price matches
                                if (exchange.getOrchidBuyOrders().back().Quantity == order.Quantity){ // quantity matches
                                    // remove the buy order
                                    Order sold = exchange.getOrchidBuyOrders().back();
                                    exchange.getOrchidBuyOrders().pop_back();

                                    // record the output of sell
                                    order.status = "Fill";
                                    output.str("");
                                    output << order.Order_ID << "," << order.Client_Order << "," << order.Instrument << "," << order.Side << "," << order.status << "," << order.Quantity << "," << sold.Price;
                                    outputFile << output.str() << std::endl;

                                    // record the output of buy
                                    sold.status = "Fill";
                                    output.str("");
                                    output << sold.Order_ID << "," << sold.Client_Order << "," << sold.Instrument << "," << sold.Side << "," << sold.status << "," << order.Quantity << "," << sold.Price;
                                    outputFile << output.str() << std::endl;
                                    break; 
                                }
                                else if (exchange.getOrchidBuyOrders().back().Quantity > order.Quantity){ 
                                    // record the output of buy
                                    Order sold = exchange.getOrchidBuyOrders().back();
                                    sold.status = "PFill";
                                    output.str("");
                                    output << sold.Order_ID << "," << sold.Client_Order << "," << sold.Instrument << "," << sold.Side << "," << sold.status << "," << order.Quantity << "," << sold.Price;
                                    outputFile << output.str() << std::endl;
                                    
                                    // record the output of sell order
                                    order.status = "Fill";
                                    output.str("");
                                    output << order.Order_ID << "," << order.Client_Order << "," << order.Instrument << "," << order.Side << "," << order.status << "," << order.Quantity << "," << sold.Price;
                                    outputFile << output.str() << std::endl;

                                    // change the quantity
                                    exchange.getOrchidBuyOrders().back().Quantity = exchange.getOrchidBuyOrders().back().Quantity - order.Quantity;
                                    
                                }
                                else { // selling quantity is higher than buying quantity

                                    // remove the buy order
                                    Order sold = exchange.getOrchidBuyOrders().back();
                                    exchange.getOrchidBuyOrders().pop_back();
                                    
                                    // record the output of buy
                                    sold.status = "Fill";
                                    output.str("");
                                    output << sold.Order_ID << "," << sold.Client_Order << "," << sold.Instrument << "," << sold.Side << "," << sold.status << "," << sold.Quantity << "," << sold.Price;
                                    outputFile << output.str() << std::endl;

                                    // record the output of sell
                                    order.status = "PFill";
                                    order.Quantity = order.Quantity - sold.Quantity;
                                    output.str("");
                                    output << order.Order_ID << "," << order.Client_Order << "," << order.Instrument << "," << order.Side << "," << order.status << "," << sold.Quantity << "," << sold.Price;
                                    outputFile << output.str() << std::endl;
                                }
                                
                            }
                        }
                    }
                }


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
