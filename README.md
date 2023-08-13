# food-delivery-booking
This project is a food delivery booking system implemented using Object-Oriented Programming (OOP) concepts in C++. The system handles various functions related to food delivery, such as booking orders, assigning delivery executives, assigning delivery charge to executive and calculating delivery charge to the delivery executive.


Table of Contents
Introduction
Functions
1. handle booking function
2. Delivery Executive Assignment Function
3. Function to display deliveryexecutive's activity thus far.
Introduction
The Food Delivery Booking System is designed to streamline the process of ordering and delivering food to customers. This project is implemented in C++ using the principles of Object-Oriented Programming to ensure modularity, reusability, and maintainability of the codebase.

Functions
1. Handle booking function
The booking function is responsible for allowing customers to place orders for food delivery. It gathers relevant information about the order, such as Restaurant name ,delivery address , and time of placing order. Once the booking is confirmed, the system processes the order and prepares it for delivery.Code for the function is given here.

    void handleBooking(Order order) {
        bookingId++;
        orders[bookingId] = order;
        cout << "Booking ID : " << bookingId << endl;

        cout << "Available Executives :" << endl;
        cout << "Executive\tDelivery Charge Earned" << endl;
        for (auto& executive : deliveryExecutives) {
            cout << executive.name << "\t\t" << executive.deliveryChargeEarned << endl;
        }

        DeliveryExecutive* chosenExecutive = assignDeliveryExecutive(order);//it gets the assigned deliveryexecutive to the chosenExecutive
        if (chosenExecutive == nullptr) {
            cout << "No available delivery executive at the moment." << endl;
            return;
        }

        if (chosenExecutive->lastTripTime =="")
        chosenExecutive->lastTripTime = order.time;

        int deliveryCharge;
        if (chosenExecutive->combinedOrderCount >= 1 ) {
            deliveryCharge = 50 + 5 * (chosenExecutive->combinedOrderCount - 1);//this  is used to calculate the delivery charge
        } else {
            deliveryCharge = 50;
        }
        
        chosenExecutive->deliveryChargeEarned = deliveryCharge;
        chosenExecutive->lastTripTime = order.time;
        chosenExecutive->dest = order.destination;
        chosenExecutive->rest=order.restaurant;

        cout << "Allotted Delivery Executive: " << chosenExecutive->name << endl;
        chosenExecutive->droptime=drop(chosenExecutive,order.time);//this ia a calling function to calculate the time todropping point ie +30 minutes
        
    }

2. Delivery Executive Assignment Function
This function plays a crucial role in efficiently managing the delivery process. Once an order is placed, the system uses this function to assign an available delivery executive to the order. The delivery executive is alloted based on the availability of delivery executive, delivery charge earned by executive and number of combined orders for the executive. A executive can take maximum of 5 orders at a time. code is given below
DeliveryExecutive* assignDeliveryExecutive(Order order) {
        DeliveryExecutive* chosenExecutive = nullptr;
        int minCharge = INT_MAX;

        for (auto& executive : deliveryExecutives) {
            if (getTimeDifference(order.time, executive.lastTripTime) >15) {
                if (executive.deliveryChargeEarned < minCharge) {
                    chosenExecutive = &executive;
                    minCharge = executive.deliveryChargeEarned;//this function assigns executive to the order based on the condition . if the order time is less than 15 mins and with same destination it sassigns same delivery executive
                                                                  
                }
            }
            else{
                if(executive.dest==order.destination&&executive.orderCount<5)//it checks the combined order count<5
                {
                    chosenExecutive=&executive;
                    executive.combinedOrderCount++;
                    
                    break;
                }
            }
        }
       chosenExecutive->orderCount++;
        return chosenExecutive;
    }


3. Function to display deliveryexecutive's activity thus far
To monitor the activities of delivery executives and ensure that deliveries are executed smoothly, this function keeps track of their actions. It records information such as the time of placing order, arrival at the destination. This data can be later utilized for performance evaluation and improving the overall delivery process. 
 


By incorporating these three key functions, the Food Delivery Booking System enhances the user experience, optimizes delivery operations, and provides insights for continuous improvement.
Entire code is given in cpp file
