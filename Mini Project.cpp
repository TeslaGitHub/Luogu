#include <stdio.h>
#include <conio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include <cstdio>
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)

const int MaxNameLen = 20;
const int MaxSchoolNameLen = 50;
const int width = 15;
const int precision = 5;
char tmp_ch;//To empty buff

void list();
void add();
void del();
void search();
void exit();
double deg2rad(double);
double greatCircleDistance(double, double, double, double);

struct contact
{
	char name[MaxNameLen], school[MaxSchoolNameLen];
	double lat, lon;
	struct contact* next;
};

FILE* contacts, * schools;
struct contact* head = NULL;
const double longitudeUSTC = 117.269603, latitudeUSTC = 31.836854;

int main()
{
	char cmd;
	struct contact* curr = NULL, * prev = NULL;
	char name[MaxNameLen], school_name[MaxSchoolNameLen];
	double lat, lon;
	schools = fopen("schools.txt", "a+");
	contacts = fopen("contacts.txt", "r+");
	if (schools == NULL || contacts == NULL)
	{
		fprintf(stderr, "Error opening file\n");
		exit(0);
	}

	/*Read the file"contacts.txt" and set up LinkedList*/
	head = (struct contact*)malloc(sizeof(struct contact));
	prev = head;
	curr = head;
	while ((fscanf(contacts, "%s%s%lf%lf", curr->name, curr->school, &curr->lon, &curr->lat) != EOF))
	{
		prev = curr;
		curr->next = (struct contact*)malloc(sizeof(struct contact));
		curr = curr->next;
	}
	if (curr == head)
		head = NULL;
	else
		prev->next = NULL;
	free(curr);

	/*Instructions*/
	printf(
		"Instructions: \n"
		"Press L to list all the contacts\n"
		"Press A to add a contact\n"
		"Press D to delete a contact\n"
		"Press S to search for a contact\n"
		"Press E to exit the program\n");

	while (true)
	{
		printf("\nPlease enter your command\n");
		cmd = getche();
		printf("\n");
		switch (cmd)
		{
		case 'l':
		case 'L':
			list();
			break;
		case 'a':
		case 'A':
			add();
			break;
		case 'd':
		case 'D':
			del();
			break;
		case 's':
		case 'S':
			search();
			break;
		case 'e':
		case 'E':
			exit();
			return 0;
		default:
			printf("%c is no a command. \n\n", cmd);
		}
	}
	return 0;
}

void list()
{
	struct contact* curr = head;
	if (curr == NULL)
		fprintf(stdout, "No contact");
	else
		fprintf(stdout, "%-*s%-*s%-*s%-*s%-*s\n\n", MaxNameLen + 1, "NAME", MaxSchoolNameLen + 1, "SCHOOL", width + 1, "LONGITUDE", width + 1, "LATITUDE", width + 1, "DISTANCE(km)");
	while (curr)
	{
		fprintf(stdout, "%-*s %-*s %-*.*lf %-*.*lf %-*.*lf\n", MaxNameLen, curr->name, MaxSchoolNameLen, curr->school, width, precision, curr->lon, width, precision, curr->lat, width, precision, greatCircleDistance(curr->lon, curr->lat, longitudeUSTC, latitudeUSTC));
		curr = curr->next;
	}
	printf("\n\n");
	return;
}

void add()
{
	fseek(schools, 0L, SEEK_SET);
	struct contact* curr = head, * prev = head, * New;
	char school_t[MaxSchoolNameLen];
	double lon, lat, distance;
	bool sch_exsit = false;
	New = (struct contact*)malloc(sizeof(struct contact));
	fprintf(stdout, "Please enter the name and school of the contact to add\n");
	scanf("%s%s", New->name, New->school);
	if ((tmp_ch = getchar()) != '\n')
	{
		printf("\nInput error!\n");
		while ((tmp_ch = getchar()) != '\n' && tmp_ch != EOF);//Empty buff
		return;
	}

	/*To find out if the contact exits*/
	while (curr)
	{
		if (!strcmp(curr->name, New->name))
		{
			fprintf(stdout, "The contact exists already\n\n");
			free(New);
			return;
		}
		prev = curr;
		curr = curr->next;
	}
	/*To find out if the information of the school exits*/
	while (fscanf(schools, "%s%lf%lf", school_t, &lon, &lat) != EOF)
	{
		if (!strcmp(New->school, school_t))
		{
			sch_exsit = true;
			break;
		}
	}
	/*Ask user to add information*/
	if (!sch_exsit)
	{
		printf("Please enter the longitude and latitude of the contact's university\n");
		if (scanf("%lf%lf", &lon, &lat) == 2&& (tmp_ch = getchar())=='\n')
			fprintf(schools, "%s %lf %lf\n", New->school, lon, lat);
		else
		{
			while ((tmp_ch = getchar()) != '\n' && tmp_ch != EOF);//Empty buff
			printf("Input error, try again\n");
			return;
		}
	}
	printf("Contact is added\n\n");

	/*To find the right position for the new contact according to distance*/
	New->lon = lon;
	New->lat = lat;
	distance = greatCircleDistance(lon, lat, longitudeUSTC, latitudeUSTC);
	curr = head;
	prev = head;
	if (head == NULL)
	{
		head = New;
		New->next = NULL;
		return;
	}
	while (curr)
	{
		if (greatCircleDistance(curr->lon, curr->lat, longitudeUSTC, latitudeUSTC) > distance)
		{
			if (curr == head)
			{
				New->next = head;
				head = New;
			}
			else
			{
				prev->next = New;
				New->next = curr;
			}
			return;
		}
		prev = curr;
		curr = curr->next;
	}

		/*If new distance is the longest*/
	prev->next = New;
	New->next = NULL;
	return;
}

void del()
{
	struct contact* curr = head, * prev = head;
	char name[MaxNameLen];
	fprintf(stdout, "Please enter the name of the contact to delete\n");
	scanf("%s", name);
	if ((tmp_ch = getchar()) != '\n')
	{
		printf("\nInput error!\n");
		while ((tmp_ch = getchar()) != '\n' && tmp_ch != EOF);//Empty buff
		return;
	}
	while (curr)
	{
		if (!strcmp(curr->name, name))
		{
			fprintf(stdout, "Contact %s is deleted\n\n", name);
			if (curr == head)
				head = curr->next;
			else
				prev->next = curr->next;
			free(curr);
			return;
		}
		prev = curr;
		curr = curr->next;
	}
	fprintf(stdout, "No contact found\n\n");
	return;
}

void search()
{
	struct contact* curr = head, * prev = head;
	char name[MaxNameLen];
	fprintf(stdout, "Please enter the name of the contact to search for\n");
	scanf("%s", name);
	if ((tmp_ch = getchar()) != '\n')
	{
		printf("\nInput error!\n");
		while ((tmp_ch = getchar()) != '\n' && tmp_ch != EOF);//Empty buff
		return;
	}
	while (curr)
	{
		if (!strcmp(curr->name, name))
		{
			fprintf(stdout, "\n\n%-*s%-*s%-*s%-*s%-*s\n\n", MaxNameLen + 1, "NAME", MaxSchoolNameLen + 1, "SCHOOL", width + 1, "LONGITUDE", width + 1, "LATITUDE", width + 1, "DISTANCE(km)");
			fprintf(stdout, "%-*s %-*s %-*.*lf %-*.*lf %-*.*lf\n\n", MaxNameLen, curr->name, MaxSchoolNameLen, curr->school, width, precision, curr->lon, width, precision, curr->lat, width, precision, greatCircleDistance(curr->lon, curr->lat, longitudeUSTC, latitudeUSTC));
			return;
		}
		prev = curr;
		curr = curr->next;
	}
	fprintf(stdout, "No contact found\n\n");
	return;
}

void exit()
{
	struct contact* curr = head, * prev = head;
	fclose(contacts);
	contacts = fopen("contacts.txt", "w+");

	/*Write date & free storage*/
	while (curr)
	{
		fprintf(contacts, "%s %s %lf %lf\n", curr->name, curr->school, curr->lon, curr->lat);
		if (prev != head)
			free(prev);
		prev = curr;
		curr = curr->next;
	}
	free(prev);
	fclose(contacts);
	fclose(schools);
}

double deg2rad(double deg) {
	static const double PI = acos(-1.0);
	return deg * PI / 180.0;
}

double greatCircleDistance(double long1, double lat1, double long2,
	double lat2) {
	if (lat1 == lat2 && long1 == long2)
		return 0.0;
	static const double R = 6371.393; // Radius of the Earth, in km
	return R * acos(cos(deg2rad(lat1)) * cos(deg2rad(lat2)) *
		cos(deg2rad(long1 - long2)) +
		sin(deg2rad(lat1)) * sin(deg2rad(lat2)));
}