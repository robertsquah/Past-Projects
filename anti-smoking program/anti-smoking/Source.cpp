#include <iostream>
#include <string>
#include <conio.h>
#include <mysql.h> //libmysql
#include <iomanip>
#include <cctype>
using namespace std;

int main();
void WardenMenu(string);
void StudentMenu(string);
void Studentlogin();
void Wardenlogin();
void ReportSmoker(string);
void ViewTotalFine(string);
void ViewReportStatus(string);
void PayFine(string);
void CreateSummonTicket(string);
void GenerateHeavySmokerList(string);
void ReadReport(string);
void Registration();
void UpdateFine(string);
void UpdateReportStatus(string);
void DeleteReport(string);

int qstate;
MYSQL* conn;
MYSQL_ROW row;
MYSQL_RES* res;
class db_response
{
public:
	static void ConnectionFunction()
	{
		conn = mysql_init(0);
		if (conn)
			cout << "Database Connected" << endl;
		else
			cout << "Failed To Connect!" << endl;
		conn = mysql_real_connect(conn, "localhost", "root", "", "anti-smoking", 3306,
			NULL, 0);
		if (conn)
			cout << "Database Connected To MySql" << endl;
		else
			cout << "Failed To Connect!" << endl;
	}
};


int main()
{
	system("cls");
	db_response::ConnectionFunction();
	char menu;
	cout << "--------------------------------" << endl;
	cout << " Welcome to Anti-Smoking System " << endl;
	cout << "--------------------------------" << endl;
	cout << endl;
	cout << "1. Student Login" << endl;
	cout << "2. Warden Login" << endl;
	cout << "3. Exit" << endl;
	cout << "Enter your choice (Number 1 - 3only): ";
	cin >> menu;

	while (menu != '1' && menu != '2' && menu != '3') {
		cout << "Invalid Choice" << endl;
		cout << "Please re-enter your option: " << endl;
		cin >> menu;
	}
	if (menu == '1') {
		Studentlogin();
	}
	else if (menu == '2') {
		Wardenlogin();
	}
	else if (menu == '3') {
		exit(3);
	}
	else {
		cout << "Invalid Choice! Only numeric number! Please enter again! ";
		cout << "\n";
		system("pause");
		main();
	}

}

void Studentlogin()
{
	system("cls");
	string password, studentid;

	cout << "---------------" << endl;
	cout << " STUDENT LOGIN " << endl;
	cout << "---------------" << endl;
	cout << "Student ID: " << endl;
	cin >> studentid;
	cout << "Password: " << endl;
	char ch;
	while ((ch = _getch()) != 13)
	{
		password += ch;
		cout << '*';
	}

	string checkUser_query = "select Student_Id from Student where Student_Id = '" + studentid + "' and Student_Password ='" + password + "'";
	const char* cu = checkUser_query.c_str();
	qstate = mysql_query(conn, cu);

	if (!qstate) {
		res = mysql_store_result(conn);
		if (res->row_count == 1) {
			while (row = mysql_fetch_row(res))
				studentid = row[0];
			StudentMenu(studentid);
		}
		else
		{
			char c;
			cout << "Invalid Student ID or Password. Want to try again? (y/n): ";
			cin >> c;
			if (c == 'y' || c == 'Y')
				Studentlogin();
			else
				main();
		}
	}
	else
		cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
}

void Wardenlogin()
{
	system("cls");
	string password;
	string wardenid;

	cout << "--------------" << endl;
	cout << " WARDEN LOGIN " << endl;
	cout << "--------------" << endl;
	cout << "Warden ID: " << endl;
	cin >> wardenid;
	cout << "Password: " << endl;
	char ch;
	while ((ch = _getch()) != 13)
	{
		password += ch;
		cout << '*';
	}

	string checkUser_query = "select Warden_Id from Warden where Warden_Id = '" + wardenid + "' and Warden_Password ='" + password + "'";
	const char* cu = checkUser_query.c_str();
	qstate = mysql_query(conn, cu);

	if (!qstate) {
		res = mysql_store_result(conn);
		if (res->row_count == 1) {
			while (row = mysql_fetch_row(res))
				wardenid = row[0];
			WardenMenu(wardenid);
		}
		else
		{
			char c;
			cout << endl << "Invalid Warden ID or Password. Want to try again? (y/n): ";
			cin >> c;
			if (c == 'y' || c == 'Y')
				Wardenlogin();
			else
				main();
		}
	}
	else
		cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
}

void StudentMenu(string studentid)
{
	char menu;
	system("cls");
	cout << "-------------------" << endl;
	cout << " STUDENT MAIN MENU " << endl;
	cout << "-------------------" << endl;
	cout << "[1] Report Smoker" << endl;
	cout << "[2] View Report Status" << endl;
	cout << "[3] View Total Fine" << endl;
	cout << "[4] Pay Fine" << endl;
	cout << "[5] Logout" << endl;
	cout << "Enter your choice (1, 2, 3, 4, 5): ";

	cin >> menu;
	switch (menu) {
	case '1':
		ReportSmoker(studentid);
		break;
	case '2':
		ViewReportStatus(studentid);
		break;
	case '3':
		ViewTotalFine(studentid);
		break;
	case '4':
		PayFine(studentid);
		break;
	case '5':
		main();
		break;
	default:
		cout << "Please choose between 1-5.";
		system("pause");
		system("cls");
		StudentMenu(studentid);
		break;

	}
}

void WardenMenu(string wardenid)
{
	char menu;

	system("cls");
	cout << "--------------------" << endl;
	cout << " WARDEN MAIN MENU " << endl;
	cout << "--------------------" << endl;
	cout << "[1] Read Report" << endl;
	cout << "[2] Update Report Status" << endl;
	cout << "[3] Create Summon Ticket" << endl;
	cout << "[4] Generate Heavy Smoker List" << endl;
	cout << "[5] Update Smoker Fine" << endl;
	cout << "[6] Register New Student/Warden & Password Recovery" << endl;
	cout << "[7] Delete Report" << endl;
	cout << "[8] Logout" << endl;
	cout << "Enter your choice (1, 2, 3, 4, 5, 6, 7, 8): ";

	cin >> menu;
	switch (menu) {
	case '1':
		ReadReport(wardenid);
		break;
	case '2':
		UpdateReportStatus(wardenid);
		break;
	case '3':
		CreateSummonTicket(wardenid);
		break;
	case '4':
		GenerateHeavySmokerList(wardenid);
		break;
	case '5':
		UpdateFine(wardenid);
		break;
	case '6':
		Registration();
	case '7':
		DeleteReport(wardenid);
	case '8':
		main();
		break;
	default:
		cout << "Please choose between 1-9.";
		system("pause");
		system("cls");
		WardenMenu(wardenid);
		break;

	}
}
void ReportSmoker(string studentid)
{
    system("cls");
    cout << "---------------" << endl;
    cout << " REPORT SMOKER " << endl;
    cout << "---------------" << endl;
    string reportid, status = "Pending", roomno, wardenid;

    cin.ignore(1, '\n');
    cout << "___ Report Smoker___" << endl;
    cout << "Enter Room Number: ";
    getline(cin, roomno);
    while(stoi(roomno) < 0 || stoi(roomno) > 100)
    {
       cout << "Invalid room number, Room number should be between 0 and 100. Please re-enter the room number: ";
       getline(cin, roomno);
    }
    cout << endl << setw(20) << " Working Days" << setw(20) << "Warden ID" << setw(20) << "Name" << endl;
    cout << setw(20) << "Mon,Tue,Wed" << setw(20) << "W001" << setw(20) << "Quah" << endl;
    cout << setw(20) << "Thur,Fri " << setw(20) << "W002" << setw(20) << "King" << endl;
    cout << setw(20) << "Sat,Sun " << setw(20) << "W003" << setw(20) << "Fiona" << endl << endl;
    cout << "Enter Warden ID: ";
    getline(cin, wardenid);
	wardenid[0] = toupper(wardenid[0]);

	string search_query = "SELECT MAX(Report_Id) FROM Report ORDER BY Report_Id DESC LIMIT 1;";
	const char* q = search_query.c_str();
	qstate = mysql_query(conn, q);
	if (!qstate)
	{
		res = mysql_store_result(conn);
		while (row = mysql_fetch_row(res))
		{
			string prev_report_id = row[0];
			int id = stoi(prev_report_id.substr(1));
			id++;
			int report_id = id;
			reportid = "R" + string(3 - to_string(report_id).length(), '0') + to_string(report_id);
		}
	}
	else
	{
		cout << "There's no any result about this Student ID! " << endl;
		cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
	}

    string insertreport_query = "insert into Report (Report_Id, Report_Status, Report_Roomno, Student_Id, Warden_Id) values ('" + reportid + "','" + status + "','" + roomno + "','" + studentid + "','" + wardenid + "')";
    const char* p = insertreport_query.c_str();
    qstate = mysql_query(conn, p);

    if (!qstate) {
        cout << endl << "Your report have been reqistered. ";
        system("pause");
        StudentMenu(studentid);
    }
    else {
        cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
    }
}


void ViewReportStatus(string studentid)
{
	system("cls");
	cout << "---------------------" << endl;
	cout << " VIEW REPORT STATUS " << endl;
	cout << "---------------------" << endl;
	string search_query = "SELECT Report.Report_Id, Report.Report_Status, Report.Report_Roomno, Report.Warden_Id, Warden.Warden_Name FROM Report JOIN Warden ON Report.Warden_Id = Warden.Warden_Id WHERE Student_Id ='" + studentid + "' ORDER BY Report.Report_Id ASC";
	const char* q = search_query.c_str();
	qstate = mysql_query(conn, q);

	if (!qstate)
	{
		res = mysql_store_result(conn);
		while (row = mysql_fetch_row(res))
		{
			cout << "Report ID: " << row[0] << endl;
			cout << "Report Status: " << row[1] << endl;
			cout << "Room Number: " << row[2] << endl;
			cout << "Warden ID: " << row[3] << endl;
			cout << "Warden Name: " << row[4] << endl << endl;
		}


		cout << endl << "Above is the latest status for your report.";
		system("pause");
		StudentMenu(studentid);

	}
	else
	{
		cout << "You have not made any reports " << endl;
		cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
		system("pause");
		StudentMenu(studentid);
	}
}

void ViewTotalFine(string studentid)
{
	system("cls");
	cout << "------------------" << endl;
	cout << " VIEW TOTAL FINE " << endl;
	cout << "------------------" << endl;

	string search_query = "select s.Student_Id, s.Student_Name, s.Student_Roomno, t.Ticket_Fine FROM summon_ticket t, student s where t.Student_Id = s.Student_Id AND t.Student_Id ='" + studentid + "' ";
	const char* q = search_query.c_str();
	qstate = mysql_query(conn, q);

	if (!qstate)
	{
		res = mysql_store_result(conn);
		while (row = mysql_fetch_row(res))
		{
			cout << "Student ID: " << row[0] << endl;
			cout << "Name: " << row[1] << endl;
			cout << "Room Number: " << row[2] << endl;
			cout << "Total Fine: RM" << row[3] << endl;
		}
		system("pause");
		StudentMenu(studentid);

	}
	else
	{
		cout << "You have not made any reports " << endl;
		cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
	}
}


void PayFine(string studentid) {
	system("cls");
	cin.ignore(1, '\n');
	double payment, ticket_fine = 0;
	cout << "------------------------" << endl;
	cout << " PAY SUMMON TICKET FINE " << endl;
	cout << "------------------------" << endl;

	string search_query = "select s.Student_Id, s.Student_Name, s.Student_Roomno, t.Ticket_Fine FROM summon_ticket t, student s where t.Student_Id = s.Student_Id AND t.Student_Id ='" + studentid + "'  ";
	const char* q = search_query.c_str();
	qstate = mysql_query(conn, q);

	if (!qstate)
	{
		res = mysql_store_result(conn);
		while (row = mysql_fetch_row(res))
		{
			cout << "Student ID: " << row[0] << endl;
			cout << "Name: " << row[1] << endl;
			cout << "Room Number: " << row[2] << endl;
			cout << "Total Fine: RM" << row[3] << endl;
			ticket_fine = atof(row[3]);
		}

		cout << "Amount To Pay: RM";
		cin >> payment;


		if (payment > 0 && payment <= ticket_fine  ) {
			string update_query = "update summon_ticket set Ticket_Fine = (Ticket_Fine - '" + to_string(payment) + "')  where Student_Id = '" + studentid + "'";
			const char* q = update_query.c_str();
			qstate = mysql_query(conn, q);

			cout << endl << "Your payment have been accepted. ";
			system("pause");
			StudentMenu(studentid);
		}
		else {
			cout << "You can only pay up to " << ticket_fine << endl;
			system("pause");
			PayFine(studentid);
		}
		string update_query = "update summon_ticket set Ticket_Fine = (Ticket_Fine - '" + to_string(payment) + "')  where Student_Id = '" + studentid + "'";
		const char* q = update_query.c_str();
		qstate = mysql_query(conn, q);

		cout << endl << "Your payment have been accepted.";
		system("pause");
		StudentMenu(studentid);
	}

	else
	{
		cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
		system("pause");
		main();
	}
}

void ReadReport(string wardenid)
{
	system("cls");
	cout << "--------------------------" << endl;
	cout << " READ REPORT FROM STUDENT " << endl;
	cout << "--------------------------" << endl;
	cout << "\t\t\t\t--- View Report Status---" << endl;
	string search_query = "SELECT Report_Id, Report_Status, Report_Roomno, Student.Student_Name, Student.Student_Kediaman FROM Report JOIN Student ON Report.Student_Id = Student.Student_Id WHERE Report.Warden_Id ='" + wardenid + "'";
	const char* q = search_query.c_str();
	qstate = mysql_query(conn, q);
	if (!qstate)
	{
		cout << setw(11) << "Report ID" << setw(17) << "Status" << setw(20) << "Room Number" << setw(20) << "Student Name" << setw(25) << "Student Kediaman" << endl;
		res = mysql_store_result(conn);
		while (row = mysql_fetch_row(res))
		{
			cout << setw(11) << row[0] << setw(17) << row[1] << setw(20) << row[2] << setw(20) << row[3] << setw(20) << row[4] << endl;
		}
		system("pause");
		WardenMenu(wardenid);
	}
	else
	{
		cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
		system("pause");
		WardenMenu(wardenid);
	}
}



void UpdateReportStatus(string wardenid) {
	system("cls");
	char choose;
	cin.ignore(1, '\n');
	string status = "CHECKED";
	string reportid;
	cout << "----------------------" << endl;
	cout << " UPDATE REPORT STATUS " << endl;
	cout << "----------------------" << endl;
	string search_query = "SELECT Report_Id, Report_Status, Report_Roomno, Student.Student_Name, Student.Student_Kediaman FROM Report JOIN Student ON Report.Student_Id = Student.Student_Id WHERE Report.Warden_Id ='" + wardenid + "'";
	const char* q = search_query.c_str();
	qstate = mysql_query(conn, q);
	if (!qstate)
	{
		cout << setw(11) << "Report ID" << setw(17) << "Status" << setw(20) << "Room Number" << setw(20) << "Student Name" << setw(25) << "Student Kediaman" << endl;
		res = mysql_store_result(conn);
		while (row = mysql_fetch_row(res))
		{
			cout << setw(11) << row[0] << setw(17) << row[1] << setw(20) << row[2] << setw(20) << row[3] << setw(20) << row[4] << endl;
		}

		cout << "Enter the Report ID:";
		cin >> reportid;

		string update_query = "update Report set Report_Status = '" + status + "'  where Report_Id = '" + reportid + "'";
		const char* q = update_query.c_str();
		qstate = mysql_query(conn, q);

		cout << "Do you want to update other report? (y/n): ";
		cin >> choose;

		if (choose == 'y' || choose == 'Y')
			UpdateReportStatus(wardenid);
		else
			WardenMenu(wardenid);


	}
	else
	{
		cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
	}

}


void CreateSummonTicket(string wardenid) {

	system("cls");
	cin.ignore(1, '\n');
	int ticketfine;
	char choose;
	string ticketid, studentid;
	cout << "------------------------" << endl;
	cout << " CREATE SUMMON TICKET " << endl;
	cout << "------------------------" << endl;
	qstate = mysql_query(conn, "select Ticket_Id, Student_Id, Warden_Id, Ticket_Fine from summon_ticket");
	if (!qstate) {

		cout << setw(11) << "Ticket ID" << setw(17) << "Student ID" << setw(20) << "Warden ID" << setw(20) << "Ticket Fine" << endl;

		res = mysql_store_result(conn);
		while (row = mysql_fetch_row(res))
		{
			cout << setw(11) << row[0] << setw(17) << row[1] << setw(20) << row[2] << setw(20) << row[3] << endl;
		}
	}
	else {
		cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
		system("pause");
		WardenMenu(wardenid);
	}

	cout << "Do you want to register new smoker? (y/n): ";
	cin >> choose;
	if (choose == 'y' || choose == 'Y')
	{
		cout << "___ Create Summon Ticket ___" << endl;
		string search_query = "SELECT MAX(Ticket_Id) FROM summon_ticket ORDER BY Ticket_Id DESC LIMIT 1;";
		const char* q = search_query.c_str();
		qstate = mysql_query(conn, q);
		if (!qstate)
		{
			res = mysql_store_result(conn);
			while (row = mysql_fetch_row(res))
			{
				cout << "Previous Ticket ID: " << row[0] << endl;
			}

		}
		else
		{
			cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
		}

		cin.ignore(1, '\n');
		cout << "Enter Ticket ID: ";
		getline(cin, ticketid);
		ticketid[0] = toupper(ticketid[0]);
		cout << "Warden ID (Format: W***): ";
		getline(cin, wardenid);
		wardenid[0] = toupper(wardenid[0]);
		cout << "Enter Student ID: ";
		getline(cin, studentid);
		studentid[0] = toupper(studentid[0]);
		cout << "Enter Ticket Fine: RM";
		cin >> ticketfine;
		string insertsummonticket_query = "insert into summon_ticket (Ticket_Id, Student_Id, Warden_Id, Ticket_Fine ) values ('" + ticketid + "','" + studentid + "','" + wardenid + "','" + to_string(ticketfine) + "')";
		const char* e = insertsummonticket_query.c_str();
		qstate = mysql_query(conn, e);
		cout << "Smoker Has Been Registered Into Summon Ticket Successfully!" << endl;
		cout << "Do you want to register other smokers? (y/n): ";
		cin >> choose;

		if (choose == 'y' || choose == 'Y')
			CreateSummonTicket(wardenid);
		else
			WardenMenu(wardenid);

	}
	else
		system("pause");
	WardenMenu(wardenid);

}


void GenerateHeavySmokerList(string wardenid) {

	system("cls");
	cin.ignore(1, '\n');
	string kediaman;
	char choose;
	int fine = 100;
	cout << "----------------------------" << endl;
	cout << " GENERATE HEAVY SMOKER LIST " << endl;
	cout << "----------------------------" << endl;
	cout << "Select Kediaman [Tuah/Jebat/Kasturi]: ";
	cin >> kediaman;

	string search_query = "select t.Ticket_Id, s.Student_Kediaman, t.Student_Id, s.Student_Name, s.Student_Roomno, t.Ticket_Fine from Student s, summon_ticket t WHERE t.ticket_fine> '" + to_string(fine) + "' AND t.Student_Id = s.Student_Id AND s.Student_Kediaman= '" + kediaman + "'  ";
	const char* q = search_query.c_str();
	qstate = mysql_query(conn, q);

	if (!qstate)
	{
		cout << setw(11) << "Ticket ID" << setw(17) << "Kediaman" << setw(20) << "Student ID" << setw(20) << "Name" << setw(20) << "Room Number" << setw(20) << "Total Fine" << endl;

		res = mysql_store_result(conn);
		while (row = mysql_fetch_row(res))
		{
			cout << setw(11) << row[0] << setw(17) << row[1] << setw(20) << row[2] << setw(20) << row[3] << setw(20) << row[4] << setw(20) << row[5] << endl;
		}
		cout << "Do you want to generate list for other Kediaman? (y/n):";
		cin >> choose;
		if (choose == 'y' || choose == 'Y')
			GenerateHeavySmokerList(wardenid);
		else
			WardenMenu(wardenid);
	}
	else
	{
		cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
		system("pause");
		WardenMenu(wardenid);
	}


}

void UpdateFine(string wardenid) {
	system("cls");
	cin.ignore(1, '\n');
	char choose;
	string ticketid;
	int newfine;
	cout << "--------------" << endl;
	cout << " UPDATE FINE" << endl;
	cout << "--------------" << endl;

	qstate = mysql_query(conn, "select Ticket_Id, Student_Id, Warden_Id, Ticket_Fine from summon_ticket");
	if (!qstate) {

		cout << setw(11) << "Ticket ID" << setw(17) << "Student ID" << setw(20) << "Warden ID" << setw(20) << "Ticket Fine" << endl;

		res = mysql_store_result(conn);
		while (row = mysql_fetch_row(res))
		{
			cout << setw(11) << row[0] << setw(17) << row[1] << setw(20) << row[2] << setw(20) << row[3] << endl;
		}
		cout << "Enter the Ticket ID:";
		getline(cin, ticketid);
		ticketid[0] = toupper(ticketid[0]);
		cout << "Enter the Fine amount: RM";
		cin >> newfine;

		string update_query = "update summon_ticket set Ticket_Fine = (Ticket_Fine + '" + to_string(newfine) + "')  where Ticket_Id = '" + ticketid + "'";
		const char* q = update_query.c_str();
		qstate = mysql_query(conn, q);

		cout << "Do you want to update other Smoker Fine? (y/n): ";
		cin >> choose;

		if (choose == 'y' || choose == 'Y')
			UpdateFine(wardenid);
		else
			WardenMenu(wardenid);

	}
	else
	{
		cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
	}

}

void Registration()
{
	char userType;
	string studentid, studentpassword, studentname, kediaman;
	int studentroomno;
	system("cls");
	cout << "----------------------" << endl;
	cout << " USER REGISTRATION " << endl;
	cout << "----------------------" << endl;
	cout << "Please choose which user do you want to register?" << endl;
	cout << "[1] New Student" << endl;
	cout << "[2] New Warden" << endl;
	cout << "[3] Password Recovery" << endl;
	cout << "[4] Main Menu" << endl;
	cout << "\nYour choice (1 - 3): ";
	cin >> userType;

	if (userType == '1') {

		system("cls");
		cout << "------------------------------" << endl;
		cout << " NEW STUDENT REGISTRATION " << endl;
		cout << "------------------------------" << endl;
		cout << "Please fill in the following information: " << endl;
		cout << "Student Name: ";
		cin.ignore(1, '\n');
		getline(cin, studentname);
		cout << "Room Number: ";
		cin >> studentroomno;
		cin.ignore(1, '\n');
		string search_query = "SELECT MAX(Student_Id) FROM Student ORDER BY Student_Id DESC LIMIT 1;";
		const char* q = search_query.c_str();
		qstate = mysql_query(conn, q);
		if (!qstate)
		{
			res = mysql_store_result(conn);
			while (row = mysql_fetch_row(res))
			{
				cout << "Previous Student ID: " << row[0] << endl;
			}

		}
		else
		{
			cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
		}
		cout << "Student ID (Format: S***): ";
		getline(cin, studentid);
		studentid[0] = toupper(studentid[0]);

		cout << "Kediaman [Tuah/Jebat/Kasturi]: ";
		getline(cin, kediaman);

		cout << "Password: ";
		char ch1;
		while ((ch1 = _getch()) != 13) // 13 is the ASCII number for Enter
		{
			studentpassword += ch1;
			cout << "*";
		}

		string conStudentpassword;
		cout << endl << "Re-enter Password: ";
		char ch2;
		while ((ch2 = _getch()) != 13) // 13 is the ASCII number for Enter
		{
			conStudentpassword += ch2;
			cout << "*";
		}

		cout << "\n";

		if (conStudentpassword == studentpassword) {

			string checkStaff_query = "SELECT * FROM Student WHERE Student_ID = '" + studentid + "'";
			const char* cu = checkStaff_query.c_str();
			qstate = mysql_query(conn, cu);

			if (!qstate)
			{
				res = mysql_store_result(conn);
				if (res->row_count == 1)
				{
					cout << "Student ID is already exist.";
					system("pause");
					Registration();
				}
				else
				{
					string insertStudent_query = "insert into Student (Student_Id, Student_Password, Student_Name, Student_Roomno, Student_Kediaman) values ('" + studentid + "','" + studentpassword + "','" + studentname + "','" + to_string(studentroomno) + "','" + kediaman + "')";

					const char* q = insertStudent_query.c_str();
					qstate = mysql_query(conn, q);

					if (!qstate)
					{
						cout << endl << "You have been registered. ";
						system("pause");
						main();
					}
					else
					{
						cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
						system("pause");
						main();
					}
				}
			}
			else
			{
				cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
				main();
			}
		}

		else {
			cout << "password incorrect";
			system("pause");
			Registration();
		}

	}
	else if (userType == '2')
	{
		string wardenid, name, wardenpassword;
		system("cls");
		cout << "-------------------------" << endl;
		cout << " NEW WARDEN REGISTRATION " << endl;
		cout << "-------------------------" << endl;
		cout << "Please fill in the following information: " << endl;
		cout << "Warden Name: ";
		cin.ignore(1, '\n');
		getline(cin, name);

		string search_query = "SELECT MAX(Warden_Id) FROM Warden ORDER BY Warden_Id DESC LIMIT 1;";
		const char* q = search_query.c_str();
		qstate = mysql_query(conn, q);
		if (!qstate) {
			res = mysql_store_result(conn);
			while (row = mysql_fetch_row(res)) {
				cout << "Previous Warden ID: " << row[0] << endl;
			}
		}
		else {
			cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
		}
		cout << "Warden ID (Format: W***): ";
		getline(cin, wardenid);
		wardenid[0] = toupper(wardenid[0]);

		cout << "Password: ";
		char ch1;
		while ((ch1 = _getch()) != 13) // 13 is the ASCII number for Enter
		{
			wardenpassword += ch1;
			cout << "*";
		}

		string conwardenpassword;
		cout << endl << "Re-enter Password: ";
		char ch2;
		while ((ch2 = _getch()) != 13) // 13 is the ASCII number for Enter
		{
			conwardenpassword += ch2;
			cout << "*";
		}

		cout << "\n";

		if (conwardenpassword == wardenpassword) {

			string checkStaff_query = "SELECT * FROM Warden WHERE Warden_Id = '" + wardenid + "'";
			const char* cu = checkStaff_query.c_str();
			qstate = mysql_query(conn, cu);

			if (!qstate)
			{
				res = mysql_store_result(conn);
				if (res->row_count == 1)
				{
					cout << "Warden ID is already exist. Press Enter to Try Again...";
					cin.ignore();
					Registration();
				}
				else
				{
					string insertStaffAdmin_query = "insert into Warden (Warden_Id, Warden_Password, Warden_Name) values ('" + wardenid + "','" + wardenpassword + "','" + name + "')";

					const char* q = insertStaffAdmin_query.c_str();
					qstate = mysql_query(conn, q);

					if (!qstate)
					{
						cout << endl << "Warden has been registered.";
						system("pause");
						main();
					}
					else
					{
						cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
						system("pause");
						main();
					}
				}
			}
			else
			{
				cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
				main();
			}
		}

		else {
			cout << "password incorrect";
			system("pause");
			Registration();
		}


	}
	else if (userType == '3')
	{
		system("cls");
		cout << "-------------------" << endl;
		cout << " PASSWORD RECOVERY " << endl;
		cout << "-------------------" << endl;

		char recover;

		cout << "Who do you want to recover password?" << endl;
		cout << "[1] Warden" << endl;
		cout << "[2] Student" << endl;
		cout << "[M] Main Menu" << endl;

		cout << "\nYour choice: ";
		cin >> recover;

		if (recover == '1')
		{
			string wardenid, wardenpassword;
			cout << "Warden" << endl;
			cout << "\nPlease insert your Warden ID: " << endl;
			cin >> wardenid;

			string search_query = "SELECT Warden_Id FROM Warden WHERE Warden_Id = '" + wardenid + "'";
			const char* q = search_query.c_str();
			qstate = mysql_query(conn, q);
			if (!qstate)
			{
				res = mysql_store_result(conn);
				while (row = mysql_fetch_row(res))
				{
					wardenid = row[0];
				}
				cout << "New Password: ";
				char ch;
				while ((ch = _getch()) != 13)
				{
					wardenpassword += ch;
					cout << "*";
				}

				string update_query = "UPDATE Warden SET Warden_Password = '" + wardenpassword + "' WHERE Warden_Id = '" + wardenid + "'";
				const char* q = update_query.c_str();
				qstate = mysql_query(conn, q);
				cout << "\n Successfully Updated!" << endl;
				system("pause");
				main();
			}
			else
			{
				cout << "Sorry, no such ID exist! Please try again!" << mysql_errno(conn) << endl;
				system("pause");
				main();
			}

		}
		else if (recover == '2')
		{
			string studentid, studentpassword;
			cout << "STUDENT" << endl;
			cout << "\nPlease insert your Student ID: " << endl;
			cin >> studentid;

			string search_query = "SELECT Student_Id FROM student WHERE Student_Id = '" + studentid + "'";
			const char* q = search_query.c_str();
			qstate = mysql_query(conn, q);
			if (!qstate)
			{
				res = mysql_store_result(conn);
				while (row = mysql_fetch_row(res))
				{
					studentid = row[0];
				}
				cout << "New Password: ";
				char ch;
				while ((ch = _getch()) != 13)
				{
					studentpassword += ch;
					cout << "*";
				}

				string update_query = "UPDATE Student SET Student_Password = '" + studentpassword + "' WHERE Student_Id = '" + studentid + "'";
				const char* q = update_query.c_str();
				qstate = mysql_query(conn, q);
				cout << "\n Successfully Updated!" << endl;
				system("pause");
				main();
			}
			else
			{
				cout << "Sorry, no such ID exist! Please try again!" << mysql_errno(conn) << endl;
				system("pause");
				main();
			}

		}
		else if (recover == 'M' || recover == 'm')
		{
			main();
		}
		else
		{
			cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
			system("pause");
			main();
		}
	}


	else if (userType == '4')
	{
		main();
	}
	else
	{
		cout << "Invalid Choice! Please try again! " << endl;
		system("pause");
		Registration();
	}
}

void DeleteReport(string wardenid)
{
	string reportid;
	char confirm, choose;
	system("cls");
	cout << "-----------------------------" << endl;
	cout << "       DELETE REPORT " << endl;
	cout << "-----------------------------" << endl;

	cout << "\nHere's the list of reports found: \n" << endl;
	string search_query = "select Report_Id, Report_Status, Report_Roomno, Student_Id, Warden_Id from Report";
	const char* q = search_query.c_str();
	qstate = mysql_query(conn, q);
	cout << setw(11) << "Report ID" << setw(17) << "Report Status" << setw(20) << "Room Number" << setw(20) << "Student ID" << setw(20) << "Warden ID" << endl;
	if (!qstate)
	{
		res = mysql_store_result(conn);
		while (row = mysql_fetch_row(res))
		{

			cout << setw(11) << row[0] << setw(17) << row[1] << setw(20) << row[2] << setw(20) << row[3] << setw(20) << row[4] << endl;
		}
	}
	else
	{
		cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
		system("pause");
		DeleteReport(wardenid);
	}

	cout << "\nEnter REPORT ID: ";
	cin >> reportid;
	cout << "Are you confirm to delete this report [Y/N]: ";
	cin >> confirm;

	if (confirm == 'Y' || confirm == 'y')
	{
		//string delete_query = "DELETE FROM report where Report_Id = '" + reportid + "'";
		//const char* q = delete_query.c_str();

		string update_query = "UPDATE Report SET Report_Status = 'UNAVAILABLE' WHERE Report_Id = '" + reportid + "' ";
		const char* q = update_query.c_str();
		qstate = mysql_query(conn, q);
		if (!qstate)
		{
			cout << "Successfully delete a report! " << endl;
		}
		else
		{
			cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
			system("pause");
			WardenMenu(wardenid);
		}

		cout << "Do you want to continue other report?[Y/N]: ";
		cin >> choose;
		if (choose == 'y' || choose == 'Y')
			DeleteReport(wardenid);
		else if (choose == 'n' || choose == 'N')
			WardenMenu(wardenid);
	}
	else
	{
		system("pause");
		WardenMenu(wardenid);
	}
}


