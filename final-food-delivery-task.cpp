#include<bits/stdc++.h>
using namespace std;

class Order {
public:
    int customerId;
    string restaurant;
    string destination;
    string time;
    string na;
};

class DeliveryExecutive {
public:
    string name;
    int combinedOrderCount=1;
    int deliveryChargeEarned;
    string lastTripTime;
    int orderCount;
    string dest="";
    string rest="";
    string droptime="";
    DeliveryExecutive(string _name) : name(_name), deliveryChargeEarned(0), lastTripTime(""), orderCount(0) {}//initializing DeliveryExecutive class members
};

class DeliveryService {
private:
    vector<DeliveryExecutive> deliveryExecutives;//Created vector to store DeliveryExecutive class objects
    map<int, Order> orders;//created map to store Order class objects
    int bookingId;
    int tripCount;

public:
    DeliveryService(int numExecutives) : bookingId(0), tripCount(0) {
        for (int i = 1; i <= numExecutives; i++) {
            deliveryExecutives.push_back(DeliveryExecutive("DE" + to_string(i)));// this function push deliveryexecutivs names into the vector
        }
    }

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
                    ++executive.combinedOrderCount;
                    
                    break;
                }
            }
        }
       chosenExecutive->orderCount++;
        return chosenExecutive;
    }

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
        if (chosenExecutive->combinedOrderCount > 1 ) {
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

    void displayDeliveryHistory() {
        cout << "TRIP\tEXECUTIVE\tRESTAURANT\tDESTINATION POINT\tORDERS\tPICK-UP TIME\tDELIVERY TIME\tDELIVERY CHARGE" << endl;
      
 for (const auto& executive : deliveryExecutives) {
        if(executive.deliveryChargeEarned==0)
          break;
           tripCount++;
           cout << tripCount <<"\t"<<executive.name<<"\t\t"<<executive.rest<<"\t\t"<<executive.dest<<"\t\t\t\t"<<executive.lastTripTime<<"\t\t"<< executive.droptime<<"\t\t"<<executive.deliveryChargeEarned<< endl;
        }
        cout << "Total earned:" << endl;
        cout << "Executive\tAllowance\tDelivery Charges\tTotal" << endl;
        for (const auto& executive : deliveryExecutives) {
            if(executive.deliveryChargeEarned==0)
            break;
            int total = executive.deliveryChargeEarned + 10;
            cout << executive.name << "\t\t" << 10 << "\t\t" << executive.deliveryChargeEarned << "\t\t\t" << total << endl;
        }
    }

    

   int getTimeDifference(const string& currenttime, const string& existingOrderTime) {
    int t1_hour = 0, t1_minute = 0, t2_hour = 0, t2_minute = 0;
    
    int i = 0;
    while (isdigit(currenttime[i])) {
        t1_hour = t1_hour * 10 + (currenttime[i] - '0');
        
        i++;
    }
    i++; 
    while (isdigit(currenttime[i])) {
        t1_minute = t1_minute * 10 + (currenttime[i] - '0');
        i++;
    }
   
    i = 0;
    while (isdigit(existingOrderTime[i])) {
        t2_hour = t2_hour * 10 + (existingOrderTime[i] - '0');      // this function is used to calculate the time difference (15 minutes)
        i++;
    }
    i++; 
    while (isdigit(existingOrderTime[i])) {
        t2_minute = t2_minute * 10 + (existingOrderTime[i] - '0');
        i++;
    }
    
    int total_minutes_t1 = t1_hour * 60 + t1_minute;
    int total_minutes_t2 = t2_hour * 60 + t2_minute;
    int timeDifference = abs(total_minutes_t1 - total_minutes_t2);
    
    return timeDifference;
}
string drop(DeliveryExecutive*chosenExecutive,const string& ttime){
     int t1_hour = 0, t1_minute = 0, t3 =0;
    string h="",h2="",h3="";
    int i = 0;
    while (isdigit(ttime[i])) {
        t1_hour = t1_hour * 10 + (ttime[i] - '0');
        h=h+ttime[i];
        i++;
    }
    i++; 
    while (isdigit(ttime[i])) {
        t1_minute = t1_minute * 10 + (ttime[i] - '0');
        i++;
    }
    t3=t1_minute+30;
    if (t3>60)
    {
    h="";                                        // this function adds 30 minutes to pickup time
    t3=t3-60;
    t1_hour+=1;
    h=to_string(t1_hour);
    }
    
    h2=to_string(t3);
    h3=h2;
    if(h2.size()==1)
    {
        h2="";
        h2=h2+'0'+h3;
    }
    h=h+':'+h2;
    return h;
}

    
};

int main() {
    int n; 
    cout << "Enter the number of delivery executives: ";
    cin >> n;

    DeliveryService service(n);

    char continueBooking = 'Y';
    while (continueBooking == 'Y') {
        Order order;
        cout << "Enter Customer ID: ";
        cin >> order.customerId;
        cout << "Enter Restaurant: ";
        cin >> order.restaurant;
        cout << "Enter Destination Point: ";
        cin >> order.destination;
        cout << "Enter 24 hour Time ,don't give space(HH:MM): ";
        cin >> order.time;

        service.handleBooking(order);

        cin.ignore(numeric_limits<streamsize>::max(), '\n');// it cleares the previously given buffered input
        cout << "Do you want to continue booking? (Y/N): ";
        cin >> continueBooking;
    }

    service.displayDeliveryHistory();

    return 0;
}
