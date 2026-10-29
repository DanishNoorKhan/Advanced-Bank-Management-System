#include<iostream>
#include<string>
#include<windows.h>
#include<conio.h>
#include<iomanip>
using namespace std;

struct Loan {
	string status;
	string loanType,loan_id;
	string purpose;
	int duration,amount;
	double monthlyIncome,monthlyInstallment;
	double interestRate;
	double totalPayable;
	bool applied=false;
};

struct account {
	string accountNumber;
	string name,DOB;
	string password, phone;
	string address;
	double balance;
	bool hold=false;
	string MPIN;
	bool loanRequest = false;
	bool loanApproved = false;
	double loanAmount = 0;
	Loan loan;
};

int total=1;
account acc[50];
int currentUser=-1;

void defaultAccount() {
	acc[0].accountNumber = "3500000000000";
	acc[0].name = "Muhammad Ahmad";
	acc[0].DOB = "01/01/2005";
	acc[0].phone = "03001234567";
	acc[0].address = "Lahore";
	acc[0].password = "1234567 8";
	acc[0].MPIN = "1234";
	acc[0].balance = 50000;
	acc[0].hold = false;
}

void color(int c) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c);
}
void horizontal() {
	color(0xF1);
	for(int i = 0; i < 60; i++) {
		cout<< char(205);
	}
	color(0xF0);
}
void clearscreen() {
	system("cls");
	horizontal();
}


void box(string text) {
	string msg=text;
	color(0xF2);
	cout<<"\n============================================================\n";
	color(0xF0);
	cout<<msg;
	color(0xF2);
	cout<<"\n============================================================\n";
	color(0xF0);
}

void smallbox(string text) {
	string msg=text;
	color(0xF2);
	cout<<"\n========================================\n";
	color(0xF0);
	cout<<msg;
	color(0xF2);
	cout<<"\n========================================\n";
	color(0xF0);
}


void project_credits() {

	system("cls");
	box("                BANK MANAGEMENT SYSTEM \n                   PROJECT CREDITS");
	cout<< "\nUniversity   :                   Superior University";
	cout<< "\nCourse       :                   BS Computer Science";
	cout<< "\nProject      :                   Bank Management System\n";
   	   box("  Roll No.         Name                    Contribution");
//	cout<<"------------------------------------------------------------";
//	cout<< "\nRoll No.         Name                    Contribution";
//	cout<<"------------------------------------------------------------";
	cout<< "\n F25-451       Danish Noor             Backend Development";
	cout<< "\n F25-445       Mohhamad Ahamd          Backend Development";
	cout<< "\n F25-469       Mubashir Ali          Edge case & Logic Review ";
	cout<< "\n F25-444       Simran Wajid         Bug Testing & Idea Support";
	box("           Thank You for Reviewing Our Project");
	system("pause");
}


void appliedloan() {
	clearscreen();
	if(acc[currentUser].loan.applied) {
		cout<<"\nYou already have a loan request.\n";
		return;
	}
	Loan &loan = acc[currentUser].loan; // loan name ka refference variable
	cin.ignore();
	smallbox("           Loan Application");
//	cout<<"\n----------------- Loan Application -----------------\n";
	cout<<"Loan ID(User ID) : ";
	getline(cin,loan.loan_id);
	cout<<"Loan type(Personal/Home/Business ...) : ";
	getline(cin,loan.loanType);
	
	cout<<"Loan Purpose : ";
	getline(cin,loan.purpose);
	cout<<"Loan Amount : ";
	cin>>loan.amount;
	 if(cin.fail())
        {
            cin.clear();
            cin.ignore(1000,'\n');
            cout<< "\nInvalid Input! Please enter a number.\n";
            Sleep(1500);
            return;
        }
        
	cout<<"Monthly Income : ";
	cin>>loan.monthlyIncome;
	 if(cin.fail())
        {
            cin.clear();
            cin.ignore(1000,'\n');
            cout<< "\nInvalid Input! Please enter a number.\n";
            Sleep(1500);
            return;
        }
        if(loan.monthlyIncome <= 20000)
        {
        	cout<<"Monthly Income is not insufficient!\n";
        	return;
		}
	cout<<"Duration (Months): ";
	cin>>loan.duration;
	 if(cin.fail())
        {
            cin.clear();
            cin.ignore(1000,'\n');
            cout<< "\nInvalid Input! Please enter a number.\n";
            Sleep(1500);
            return;
        }
	loan.interestRate = 10;
	loan.totalPayable =
	    loan.amount +
	    (loan.amount * loan.interestRate / 100);
	loan.monthlyInstallment =
	    loan.totalPayable / loan.duration;
	loan.status="Pending";
	loan.applied=true;
	acc[currentUser].loanRequest=true;
	acc[currentUser].loanAmount=loan.amount;
	acc[currentUser].loanApproved=false;
	smallbox("       Loan Application Submitted \n          Status : Pending");
//	cout<<"\n================================";
//	cout<<"\nLoan Application Submitted";
//	cout<<"\nStatus : Pending";
//	cout<<"\n================================\n";
}

void approveReject() {
	string account;
	clearscreen();
	cin.ignore();
	box("                 MANAGE LOAN APPLICATIONS");
	cout<<"\nEnter Account Number : ";
	getline(cin,account);
	for(int i=0; i<total; i++) {
		if(acc[i].accountNumber==account) {
			if(!acc[i].loan.applied) {
				cout<<"\nNo Loan Request Found!";
				return;
			}
			int choice;
			cout<<"\nLoan Applicant : "
			    <<acc[i].name;
			cout<<"\nLoan Amount : "
			    <<acc[i].loan.amount;
			cout<<"\n\n1. Approve";
			cout<<"\n2. Reject";
			cout<<"\nChoice : ";
			cin>>choice;
			if(choice==1) {
				acc[i].loan.status="Approved";
				acc[i].loanApproved=true;
				acc[i].loanRequest=true;
				acc[i].balance += acc[i].loan.amount;
				cout<<"\n================================";
				cout<<"\nLoan Approved!";
				cout<<"\nAmount Added : "
				    <<acc[i].loan.amount;
				cout<<"\n================================";
			} else if(choice==2) {
				acc[i].loan.status="Rejected";
				acc[i].loanApproved=false;
				acc[i].loanRequest=true;
				box("Loan Rejected!");
//				cout<<"\n================================";
//				cout<<"\nLoan Rejected!";
//				cout<<"\n================================";
			} else {
				cout<<"\nInvalid Choice";
			}
			return;
		}
	}
	cout<<"\nAccount Not Found!\n";
	system("pause");
}

void viewLoans() {
	clearscreen();
	         
	smallbox("              Loan Status");
//	cout<<"\n========== Loan Applications ==========\n";
	bool found=false;
	for(int i=0; i<total; i++) {
		if(acc[i].loan.applied) {
			found=true;
			cout<<"\nAccount Number : "
			    <<acc[i].accountNumber;
			cout<<"\nName : "
			    <<acc[i].name;
			cout<<"\nLoan Type : "
			    <<acc[i].loan.loanType;
			cout<<"\nAmount : "
			    <<acc[i].loan.amount;
			cout<<"\nStatus : "<<acc[i].loan.status;
			cout<<"\n--------------------------------";
			system("pause");
		}
	}
	if(!found)
		cout<<"\nNo Loan Applications.";
		system("pause");
}

void loanStatus() {
	clearscreen();
	box("                          Loan Status");
//	cout<<"\n================================";
//	cout<<"\n          Loan Status";
//	cout<<"\n================================\n";
	if(!acc[currentUser].loan.applied) {
		cout<<"\nNo Loan Application Found.\n";
		return;
	}
	cout<<"\nLoan ID : "
	    <<acc[currentUser].loan.loan_id;
	cout<<"\nLoan Type : "
	    <<acc[currentUser].loan.loanType;
	cout<<"\nPurpose : "
	    <<acc[currentUser].loan.purpose;
	cout<<"\nAmount : "
	    <<acc[currentUser].loan.amount;
	cout<<"\nInterest Rate : "
	    <<acc[currentUser].loan.interestRate<<"%";
	cout<<"\nMonthly Installment : "<<acc[currentUser].loan.monthlyInstallment;
	cout<<"\nStatus : "<<acc[currentUser].loan.status;
	cout<<"\n================================\n";
}

string getPassword() {
	string pass = "";
	char ch;
	cout<< "\nPassword: ";
	while ((ch = getch()) != '\r') {
		if (ch == '\b') {
			if (!pass.empty()) {
				pass.pop_back();
				cout<< "\b \b";
			}
		} else {
			pass.push_back(ch);
			cout<< '*';
		}
	}
	cout<< endl;
	return pass;
}

string name() {
	string name;
	while(true) {
		cout<<"\nUser name : ";
		getline(cin,name);
		bool valid = true;
		if(name.length() < 3) {
			valid = false;
		} else {
			bool spaceFound = false;
			for(int i = 0; i < name.length(); i++) {
				if(name[i] == ' ')
					spaceFound = true;
				if(!isalpha(name[i]) && name[i] != ' ') {
					valid = false;
					break;
				}
			}
			if(!spaceFound)
				valid = false;
		}
		if(valid)
			return name;
		cout<< "Invalid Name! Name must contain only alphabets, include at least one space, and be at least 3 characters long.\n";
	}
	horizontal();
}

string accountno() {
	string accountNo;
	while(true) {
		cout<< "Account Number : ";
		getline(cin,accountNo);
		bool valid = true;
		for(int i=0; i<total; i++) {
			if(accountNo == acc[i].accountNumber) {
				cout<< "Account already exists. Try again\n";
				valid = false;
				break;
			}
		}
		if(accountNo.length() != 13)
			valid = false;
		else {
			for(int i=0; i<13; i++) {
				if(!isdigit(accountNo[i])) {
					valid = false;
					break;
				}
			}
		}
		if(valid)
			return accountNo;
		cout<< "\nEnter valid 13-digit CNIC\n";
	}
}

string Password() {
	string pass, dob, cnic;
	while(true) {
		cout<<"Password : ";
		getline(cin, pass);
		bool alpha=false;
		bool digit=false;
		for(int i=0; i<pass.length(); i++) {
			if(pass[i]>='A' && pass[i]<='Z') {
				alpha=true;
			}
			if(pass[i]>='0' && pass[i]<='9') {
				digit=true;
			}
		}
		if(alpha && digit && pass.length()>=8) {
			return pass;
		} else {

			cout<<"\nWeak Password\n";
			cout<<"Password must contain:\n";
			cout<<"- Minimum 8 characters\n";
			cout<<"- One capital letter\n";
			cout<<"- One digit\n";
		}
	}
}

int  clientLogin() {
	string user, password;
	clearscreen();
	cin.ignore();
	smallbox("               Client Login");
//	cout<<"\n  ===== Client Login ===== \n";
	cout<<"\nAccount Number  (e.g CNIC): ";
	getline(cin, user);
	password=getPassword();
	for(int i=0; i<total; i++) {
		if( user == acc[i].accountNumber    && password== acc[i].password ) {
			cout<<"\n================================";
			cout<<"\nLogin Successful!";
			cout<<"\nWelcome "<<acc[i].name;
			cout<<"\nYou can now access your account.";
			cout<<"\n================================\n";
			return i;
		}
	}
	cout<<"\nLogin Failed!";
	cout<<"\nIncorrect Account Number or Password.\n";
	return -1;
}

bool adminLogin() {
	string user, password;
	clearscreen();
	smallbox("             Admin Login");
//	cout<<"\n===== Admin Login ===== \n";
	cin.ignore();
	cout<<"\nUsername : ";
	getline(cin, user);
	password=getPassword();
	cin.clear();
	if(user == "@hmAd" && password == "1234567 8") {
		smallbox("       Login Successful!");
		Sleep(2000);
//		cout<<"\n================================";
//		cout<<"\nLogin Successful!";
//		cout<<"\n================================\n";
		return true;
	} else {
		smallbox("       Not found!.......");
//		cout<<"\n================================";
//		cout<<"\nNot found!.......";
//		cout<<"\n================================\n";
Sleep(500);
		return false;
	}
}

void printStatus(bool hold) {
	if(hold)
		cout<<"HOLD";
	else
		cout<<"ACTIVE";
}

void displayAccount(int i) {

	cout<<"\nAccount Number : "<<acc[i].accountNumber;
	cout<<"\nName : "<<acc[i].name;
	cout<<"\nPhone : "<<acc[i].phone;
	cout<<"\nAddress : "<<acc[i].address;
	cout<<"\nBalance : "<<acc[i].balance;
	cout<<"\nStatus : ";
	printStatus(acc[i].hold);
}

string dateofbirth() {
	string date;
	while(true) {
		cout<<"Date of Birth (DD/MM/YYYY) : ";
		getline(cin,date);
		bool valid=true;
		if(date.length()!=10 ||
		        date[2]!='/' ||
		        date[5]!='/') {
			valid=false;
		} else {
			for(int i=0; i<10; i++) {
				if(i!=2 && i!=5 && !isdigit(date[i])) {
					valid=false;
					break;
				}
			}
		}
		if(valid)
			return  date;
		cout<<"Invalid Date Format. Use DD/MM/YYYY\n";
	}
}

string phonenumber() {
	string phoneno;
	while(true) {
		cout<<"Phone : ";
		getline(cin,phoneno);
		bool valid=true;
		if(phoneno.length()!=11) {
			valid=false;
		} else if(phoneno.substr(0,2)!="03") {
			valid=false;
		} else {
			for(int i=0; i<11; i++) {
				if(!isdigit(phoneno[i])) {
					valid=false;
					break;
				}
			}
		}
		if(valid)
			return phoneno;
		cout<<"Invalid Phone Number. Example: 03XXXXXXXXX\n";
	}
}

string mpin() {
	string mpin;
	while(true) {
		cout<<"MPIN (4 digits): ";
		getline(cin,mpin);
		bool valid=true;
		if(mpin.length()!=4 && mpin== "0000") {
			valid=false;
		} else {
			for(int i=0; i<4; i++) {
				if(mpin[i]<'0' || mpin[i]>'9') {
					valid=false;
					break;
				}
			}
		}
		if(valid)
			return mpin;
		cout<<"Invalid MPIN. Enter 4 digits only.\n";
	}
}

void createAccount() {
	cin.ignore();
	clearscreen();
	if(total >= 50) {
		cout<<"Bank database is full.\n";
		return;
	}
	smallbox("           Create New Account");
//	cout<<"\n------------- New Account -------------\n";
	acc[total].accountNumber=   accountno();
	acc[total].name=  name();
	acc[total].DOB=dateofbirth();
	acc[total].phone=phonenumber();
	while(true) {
		cout<<"Address : ";
		getline(cin,acc[total].address);
		if(acc[total].address.length()>=5)
			break;
		cout<<"Address must contain minimum 5 characters.\n";
	}
	acc[total].password=  Password();
	acc[total].MPIN = mpin();
	while(true) {
		cout<<"Opening Balance : ";
		cin>>acc[total].balance;
		if(acc[total].balance>=500)
			break;
		cout<<"Minimum opening balance is 500.\n";
	}
	total++;
	cout<<"Account Created Successfully\n";
	Sleep(1000);
	return;
}

void viewAllAccounts() {
	int choice;
	string Acc;
	horizontal();
	       
	smallbox("         Different options");
//	cout<<"                Different options\n";
	cout<<"1- View specific account \n";
	cout<<"2- View all accounts\nChoice :  ";
	cin>>choice;
		if(cin.fail()) {
			cin.clear();
			cin.ignore(1000,'\n');
			cout<< "\nInvalid Input! Please enter a number.\n";
			Sleep(1500);
		}
	switch(choice) {
		case 1: {
			cin.ignore();
			bool found = false;
			clearscreen();
			smallbox("             Search Account");
//			cout<<"------------------------- Search Account -------------------------\n";
			cout<<"Account Number : ";
			getline(cin, Acc);
			for(int i=0; i<total; i++) {
				if(Acc == acc[i].accountNumber) {
					found = true;
					cout<<endl;
					cout<<"  "<<i+1<<"   \n";
					displayAccount(i);
					cout<<endl;
					cout<<" Account record displayed successfully.\n";
					cout<<"-----------------------------------\n";
				}
			}
			if(!found) {
				cout<< "Account not found!\n";
			}
		}
		break;
		case 2:
			clearscreen();
			smallbox("     All Accounts Full Details");
//			cout<<"\n-------------------- All Accounts Full Details --------------------\n";
			for(int i=0; i<total; i++) {
				cout<<endl;
				cout<<"   Account no. : "<<i+1<<"  \n";
				displayAccount( i);
				cout<<endl;
				cout<<"All account records displayed successfully.\n";
				cout<<"-----------------------------------\n";
			}
			break;
		default:
			cout<<"\nPlease enter a  valid key.\n";
			return ;
	}
	system("pause");
}

void deleteAccount() {
	string no;
	clearscreen();
	smallbox("           Delect Account ");
	cout<<"\n Account number : ";
	cin>> no;

	for(int i=0; i<total; i++) {

		if( no == acc[i].accountNumber ) {
			cout<<"\nAccount found!";
			cout<<"\nDeleting account data...\n";

			for(int j = i; j < total-1; j++) {
				acc[j] = acc[j+1];
			}
			total--;
			smallbox("Account Deleted Successfully!");
//			cout<<"\n================================";
//			cout<<"\nAccount Deleted Successfully!";
//			cout<<"\n================================\n";
			return;
		}
	}
	cout<<"\nAccount not found.\n";
	Sleep(1000);
}

void HoldAccount() {
	string account;
	cin.ignore();
smallbox("        Hold Bank Account");
	cout<<"\nAccount number : ";
	getline(cin, account);
	for(int i=0; i<total; i++) {
		if(account == acc[i].accountNumber ) {
			acc[i].hold = true;
			system("   Account Status Changed!\n     Account is now HOLD.\nCustomer cannot perform transactions.");
//			cout<<"\n================================";
//			cout<<"\nAccount Status Changed!";
//			cout<<"\nAccount is now HOLD.";
//			cout<<"\nCustomer cannot perform transactions.";
//			cout<<"\n================================\n";
			return ;
		}
	}
	cout<<"\nAccount not found!....\n";
	Sleep(1000);
}

void ReleaseAccount() {
	string account;
	cin.ignore();
	smallbox("      Release Bank Account");
	cout<<"\nAccount number : ";
	getline(cin,account);
	for(int i=0; i<total; i++) {
		if(account == acc[i].accountNumber  ) {
			acc[i].hold = false;
			cout<<"\n================================";
			cout<<"\nAccount Released Successfully!";
			cout<<"\nCustomer can now use banking services.";
			cout<<"\n================================\n";
			return ;
		}
	}
	cout<<"Account not found!....\n";
	Sleep(1000);
}

void UpdateAccount() {
	string accountNo;
	clearscreen();
	box("           UPDATE ACCOUNT INFORMATION");
	cout<<"\nEnter Account Number to Update: ";
	cin>>accountNo;
	cin.ignore();
	for(int i=0; i<total; i++) {
		if(accountNo == acc[i].accountNumber) {
			int choice;
			cout<<"\nAccount Found\n";
			cout<<"\n1. Update Name";
			cout<<"\n2. Update Date of Birth";
			cout<<"\n3. Update Phone";
			cout<<"\n4. Update Address";
			cout<<"\n5. Update Password";
			cout<<"\n6. Update MPIN";
			cout<<"\nChoice: ";
			cin>>choice;
			cin.ignore();
			switch(choice) {
				case 1:
					acc[i].name=name();
					cout<<"Name Updated Successfully\n";
					break;
				case 2:
					acc[i].DOB=dateofbirth();
					cout<<"DOB Updated Successfully\n";
					break;
				case 3:
					acc[i].phone=phonenumber();
					cout<<"Phone Updated Successfully\n";
					break;
				case 4:
					cout<<"New Address: ";
					getline(cin,acc[i].address);
					cout<<"Address Updated Successfully\n";
					break;
				case 5:
					acc[i].password=Password();
					cout<<"Password Updated Successfully\n";
					break;
				case 6:
					acc[i].MPIN=mpin();
					cout<<"MPIN Updated Successfully\n";
					break;
				default:
					cout<<"Invalid Choice\n";
			}
			return;
		}
	}
	cout<<"Account Not Found!\n";
}

void depositMoney() {
	string accountNo;
	double amount;
	cin.ignore();
	smallbox("        CASH DEPOSIT");
	cout<< "\nAccount Number : ";
	getline(cin, accountNo);
	for(int i = 0; i < total; i++) {
		if(accountNo == acc[i].accountNumber) {
			cout<< "Enter Deposit Amount : ";
			cin >> amount;
			if(amount > 0) {
				acc[i].balance += amount;
				cout<<"================================";
				cout<< "\nDeposit Successful!";
				cout<< "\nDeposited Amount : " << amount;
				cout<< "\nNew Balance : " << acc[i].balance;
				cout<<"================================\n";
			} else {
				cout<< "\nInvalid Amount!\n";
			}
			return;
		}
	}
	cout<< "\nAccount not found!\n";
}

void profile() {
	clearscreen();
	smallbox("          Client Profile");
//	cout<<"\n ----------------- Client Profile -----------------\n";
	displayAccount(currentUser);
	cout<<"\nProfile loaded successfully.";
	cout<<"\nYou can manage your account from Client Menu.\n";
	cout<<"\n-------------------------------------------------\n";
}

void transfer() {
	string account, MPIN;
	double amount;
	clearscreen();
	cin.ignore();
	smallbox("     Transaction Services");
//	cout<<"=================================";
//	cout<<" Transaction Services";
//	cout<<"=================================";
	cout<< "\nAccount Number : ";
	getline(cin, account);
	if(account == acc[currentUser].accountNumber) {
		cout<< "\nYou cannot transfer money to your own account.\n";
		return;
	}
	bool found = false;
	for(int i=0; i<total; i++) {
		if(account == acc[i].accountNumber) {
			found = true;
			if(acc[i].hold) {
				cout<< "\nTransaction Failed!";
				cout<< "\nReceiver account is blocked.\n";
				return;
			}
			if(acc[currentUser].hold) {
				cout<< "\nYour account is blocked.\n";
				return;
			}
			cout<< "\nReceiver Name : " << acc[i].name;
			cout<< "\nEnter Amount : ";
			cin >> amount;
			if(amount >= 0 && amount <100) {
				cout<< "\nInvalid amount at least greater than 100 .\n";
				return;
			}
			if(amount > acc[currentUser].balance) {
				cout<< "\nTransaction Failed!";
				cout<< "\nReason : Insufficient Balance.";
				cout<< "\nAvailable Balance : "
				     << acc[currentUser].balance << endl;
				return;
			}
			cout<< "\nEnter MPIN : ";
			cin >> MPIN;
			if(MPIN != acc[currentUser].MPIN) {
				cout<< "\nIncorrect MPIN!\n";
				return;
			}
			char choice;
			cout<< "\nConfirm Transaction (Y/N) : ";
			cin >> choice;
			if(choice!='Y' && choice!='y') {
				cout<< "\nTransaction Cancelled.\n";
				return;
			}
			acc[currentUser].balance -= amount;
			acc[i].balance += amount;
			cout<<"\n====================================";
			cout<< "\nTransaction Successful!";
			cout<< "\nTransferred Amount : " << amount;
			cout<< "\nReceiver Name      : " << acc[i].name;
			cout<< "\nReceiver Account   : " << acc[i].accountNumber;
			cout<< "\nRemaining Balance  : "
			     << acc[currentUser].balance;
			cout<<"\n====================================\n";
 
			return;
		}
	}
	if(!found) {
		cout<< "\nAccount not found.\n";
	}
}

void withdraw() {
	double amount;
	string mpin;
	clearscreen();
	smallbox("        Withdraw Money");
//	cout<<"================================";
//	cout<< "\nWithdraw Money";
//	cout<<"================================\n";
	if(acc[currentUser].hold) {
		cout<< "\nYour account is on HOLD.";
		cout<< "\nYou cannot withdraw money.\n";
		return;
	}
	cout<< "Enter Amount : ";
	cin >> amount;
	if(cin.fail()) {
		cin.clear();
		cin.ignore(1000,'\n');
		cout<< "\nInvalid amount!\n";
		return;
	}
	if(amount <= 0 || amount<500) {
		cout<< "\nInvalid Amount!\n";
		return;
	}
	if(amount > acc[currentUser].balance) {
		cout<< "\nTransaction Failed!";
		cout<< "\nReason : Insufficient Balance.";
		cout<< "\nAvailable Balance : "
		     << acc[currentUser].balance <<"";
		return;
	}
	cout<< "\nEnter MPIN : ";
	cin >> mpin;
	if(mpin != acc[currentUser].MPIN) {
		cout<< "\nWrong MPIN!";
		cout<< "\nTransaction Failed.\n";
		return;
	}
	char choice;
	cout<< "\nConfirm Withdrawal (Y/N) : ";
	cin >> choice;
	if(choice != 'Y' && choice != 'y') {
		cout<< "\nWithdrawal Cancelled.\n";
		return;
	}
	acc[currentUser].balance -= amount;
	cout<<"\n================================";
	cout<< "\nWithdrawal Successful!";
	cout<< "\nWithdraw Amount : " << amount;
	cout<< "\nRemaining Balance : "
	     << acc[currentUser].balance;
	cout<<"\n================================\n";
}

void changePassword() {
	string password;
	clearscreen();
	cin.ignore();
	smallbox("          Update Password");
//	cout<<"---------- Update Password ----------\n";
	cout<< "Enter Old Password : ";
	getline(cin, password);
	if(password == acc[currentUser].password) {
		cout<<endl;
		acc[currentUser].password = Password();
		smallbox("Password Changed Successfully!");
//		cout<<"================================";
//		cout<< "\nPassword Changed Successfully!";
//		cout<<"================================\n";
	} else {
		cout<< "\nIncorrect Old Password!\n";
		cout<< "\nPassword Not Changed.\n";
	}
}

void changeMPIN() {
	string pin;
	clearscreen();
	cin.ignore();
	smallbox("                Update MPIN ");
//	cout<<"---------- Update MPIN ----------\n";
	cout<< "Enter Old MPIN : ";
	getline(cin, pin);
	if(pin == acc[currentUser].MPIN) {
		cout<<endl;
		acc[currentUser].MPIN = mpin();
		smallbox("MPIN Changed Successfully!");
//		cout<<"================================";
//		cout<< "\nPassword Changed Successfully!";
//		cout<<"================================\n";
	} else {
		cout<< "\nIncorrect Old Password!\n";
		cout<< "\nPassword Not Changed.\n";
	}
}

void forgotPassword() {
	string accountNo, phone;
	clearscreen();
	smallbox("           Forgot Password");
//	cout<<"================================";
//	cout<<"       Forgot Password";
//	cout<<"================================\n";
	cin.ignore();
	cout<< "Enter Account Number : ";
	getline(cin, accountNo);
	for(int i=0; i<total; i++) {
		if(accountNo == acc[i].accountNumber) {
			cout<< "Enter Registered Phone Number : ";
			getline(cin, phone);
			if(phone == acc[i].phone) {
				cout<< "\nAccount Verified Successfully!\n";
				cout<< "\nEnter New Password\n";
				acc[i].password = Password();
				smallbox("Password Changed Successfully!");
//				cout<<"================================";
//				cout<< "\nPassword Changed Successfully!";
//				cout<<"================================\n";
				
				Sleep(1500);
				return;
			} else {
				cout<< "\nIncorrect Phone Number!\n";
				Sleep(1500);
				return;
			}
		}
	}
	cout<< "\nAccount Not Found!\n";
	system("pause");
}

void clientportal() {
	int choice;
	while(true) {
		clearscreen();
		smallbox("                Client Menu");
//		cout<< setw(30) <<"--------------- Client Menu ---------------\n";
		cout<< "\n1) See Profile";
		cout<< "\n2) Money Transfer";
		cout<< "\n3) View Balance";
		cout<< "\n4) Withdraw";
		cout<< "\n5) Change Password";
		cout<< "\n6) Forget MPIN";
		cout<< "\n7) Apply Loan";
		cout<< "\n8) Loan Status";
		cout<< "\n9) Logout";
		cout<< "\nChoice : ";
		cin >> choice;
		if(cin.fail()) {
			cin.clear();
			cin.ignore(1000,'\n');
			cout<< "\nInvalid Input! Please enter a number.";
			Sleep(1500);
			continue;
		}
		switch(choice) {
			case 1:
				profile();
				break;
			case 2:
				transfer();
				break;
			case 3:
				smallbox("              View Balance");
//				cout<<"==============================================";
//				cout<<"             View Balance";
//				cout<<"==============================================";
				cout<< "\nCurrent Balance : " << acc[currentUser].balance << endl;
				break;
			case 4:
				withdraw();
				break;
			case 5:
				changePassword();
				break;
			case 6:
				changeMPIN();
				break;
			case 7:
				appliedloan();
				break;
			case 8:
				loanStatus();
				break;
			case 9:
				currentUser = -1;
				smallbox("Logout Successful!\nThank you for using Bank System.");
//				cout<<"================================";
//				cout<< "\nLogout Successful!";
//				cout<< "\nThank you for using Bank System.";
//				cout<<"================================\n";
				return;
			default:
				cout<< "\nInvalid Choice! Please enter 1 to 9.\n";
		}
		cout<<"\nPress any key to continue...";
		getch();
	}
}

int main() {
	system("color F0");
    //system("color XY"); x = bakground , y = text (0,1,2,3 , .. , 9, A,B,C,D,E,F)
	//cls 2
	
	defaultAccount();
	project_credits();
	while(true) {
		clearscreen();
		int choice;
		box("                    BANK MANAGEMENT SYSTEM");
		cout<< "1) Admin\n";
		cout<< "2) Client\n";
		cout<< "3) ForgetPassword\n";
		cout<< "Choice : ";
		cin >> choice;
		
		if(cin.fail()) { //run if value is not int
			cin.clear();
			cin.ignore(1000,'\n');
			cout<< "\nInvalid Input! Please enter a number.\n";
			Sleep(1500); //mili sec and sec problem
//			sleep(1);
			continue;
		}
		switch(choice) {
			case 1: {
				if(adminLogin()) {
					bool logout = false;
					while(!logout) {
						clearscreen();
						int ch;
						smallbox("             Admin Menu");
//						cout<<"----------------------- Admin Menu -----------------------\n";
						cout<< "\n1. Create Account";
						cout<< "\n2. View Accounts";
						cout<< "\n3. Delete Account";
						cout<< "\n4. Hold Account";
						cout<< "\n5. Release Account";
						cout<< "\n6. Update Account";
						cout<< "\n7. Deposit Money";
						cout<< "\n8. View Loan Requests";
						cout<< "\n9. Manage Loan";
						cout<< "\n0. Logout";
						cout<< "\nChoice : ";
						cin >> ch;
						if(cin.fail()) {
							cin.clear();
							cin.ignore(1000,'\n');
							cout<< "\nInvalid Input!\n";
							Sleep(1500);
							continue;
						}
						switch(ch) {
							case 1:
								createAccount();
								break;
							case 2:
								viewAllAccounts();
								break;
							case 3:
								deleteAccount();
								break;
							case 4:
								HoldAccount();
								break;
							case 5:
								ReleaseAccount();
								break;
							case 6:
								UpdateAccount();
								break;
							case 7:
								depositMoney();
								break;
							case 8:
								viewLoans() ;
								break;
							case 9:
								approveReject();
								break;

							case 0:
								logout = true;
								        
								smallbox("           Logout Successful!");
//								cout<< "\nLogout Successful!\n";
								break;

							default:
								cout<< "\nInvalid Choice!\n";
								Sleep(500);
						}

						if(logout) {
							cout<< "\nPress any key to continue...";
//							system("pause");
							getch();
						}
					}
				} else {
					cout<< "\nAdmin account not found.\n";
					cout<< "Login using another admin account.\n";
					Sleep(1500);
				}
				break;
			}
			case 2: {
				int index = clientLogin();

				if(index == -1) {
					cout<< "\nClient account not found.\n";
					cout<< "Login using another account.\n";
					Sleep(1500);
				} else {
					currentUser = index;
					clientportal();
				}
				break;
			}
			case 3:
				forgotPassword();
				
				break;
			default:
				cout<< "\nInvalid Choice! Please enter 1 , 2 or 3.\n";
				Sleep(1500);
		}
	}
	return 0;
}

//36 functions , 2 gloable variables, 1 array , 2 structures , 2 outers librariesr (windows.h ,conio.h)