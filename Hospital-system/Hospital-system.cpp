#include <iostream>
#include <vector>
using namespace std;

const int MAX_SPECIALIZATION = 20;
const int MAX_PATIENTS = 5;

vector<vector<string>> patients((MAX_SPECIALIZATION + 1), vector<string>(MAX_PATIENTS + 1));
vector<vector<int>> status((MAX_SPECIALIZATION + 1), vector<int>(MAX_PATIENTS + 1));
vector<int> queue_length(MAX_SPECIALIZATION + 1);

int menu()
{
  int choice = 0;
  while (choice == 0)
  {
    cout << "Please enter your choice:\n"
         << "[1] Add new patient.\n"
         << "[2] Print all patients.\n"
         << "[3] Get next patient.\n"
         << "[4] Exit.\n";
    cin >> choice;
    if(!(choice >= 1 && choice <= 4))
    {
      cout << "Invalid choice.\n";
      choice = 0;
    }
    else break;
  }

  return choice;
}

void shift_right(int spec)
{
  int len = queue_length[spec];
  for(int i = len; i >= 0; i--)
  {
    patients[spec][i + 1] = patients[spec][i];
    status[spec][i + 1] = status[spec][i];
  }

  return;
}

void add_patient()
{
  int spec;
  string name;
  int st;

  cout << "Please enter specialization, name, and status.\n";
  cin >> spec >> name >> st;
  if(spec >= MAX_SPECIALIZATION)
  {
    cout << "Sorry, specialization unavailable.\n";
    return;
  }

  int pos = queue_length[spec];
  if(pos >= MAX_PATIENTS)
  {
    cout << "Sorry, we can't add more patients for this specialization.\n";
    return;
  }

  if(st == 0)
  {
    patients[spec][pos] = name;
    status[spec][pos] = 0;
    queue_length[spec]++;
  }
  else
  {
    shift_right(spec);
    patients[spec][0] = name;
    status[spec][0] = 1;
    queue_length[spec]++;
  }

  return;
}

void print_specialization(int spec)
{
  cout << "There are " << queue_length[spec] << " patients in specialization " << spec << ":\n";
  
  for(int i = 0; i < queue_length[spec]; i++)
  {
    cout << patients[spec][i] << " ";
    if(status[spec][i] == 0)
      cout << "Regular\n";
    else
      cout << "Urgent\n";
  }

  return;
}

void print_patients()
{
  for(int i = 0; i < patients.size(); i++)
  {
    if(queue_length[i] <= 0)
      continue;
    else
      print_specialization(i);
    cout << "====================\n";
  }

  return;
}

void get_patient()
{
  int patient_to_get;
  cout << "Enter specialization: ";
  cin >> patient_to_get;

  if(queue_length[patient_to_get] <= 0)
  {
    cout << "No patients at the moment. Have rest Doc.\n";
    return;
  }
  
  cout << patients[patient_to_get][0] << ", The doctor will see you now.\n";
  patients[patient_to_get].erase(patients[patient_to_get].begin());
  status[patient_to_get].erase(status[patient_to_get].begin());
  queue_length[patient_to_get]--;

  return;
}

void hospital_system()
{
  while(true)
  {
    int choice = menu();
    switch(choice)
    {
      case 1:
        add_patient();
        break;
      case 2:
        print_patients();
        break;
      case 3:
        get_patient();
        break;
      default:
        return;
    }
  }
}

int main()
{
  hospital_system();
  return 0;
}