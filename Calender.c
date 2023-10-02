#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE    1
#define FALSE   0

int days_in_month[]={0,31,28,31,30,31,30,31,31,30,31,30,31};
char *months[]=
{
	" ",
	"\n\n\nJanuary",
	"\n\n\nFebruary",
	"\n\n\nMarch",
	"\n\n\nApril",
	"\n\n\nMay",
	"\n\n\nJune",
	"\n\n\nJuly",
	"\n\n\nAugust",
	"\n\n\nSeptember",
	"\n\n\nOctober",
	"\n\n\nNovember",
	"\n\n\nDecember"
};

int inputyear(void)
{
	int year;
	printf("Please enter a year (example: 1999) : ");
	scanf("%d", &year);
	return year;
}

int determinedaycode(int year)
{
	int daycode;
	int d1, d2, d3;
	d1 = (year - 1.)/ 4.0;
	d2 = (year - 1.)/ 100.;
	d3 = (year - 1.)/ 400.;
	daycode = (year + d1 - d2 + d3) %7;
	return daycode;
}

int determineleapyear(int year)
{
	if(year% 4 == FALSE && year%100 != FALSE || year%400 == FALSE)
	{
		days_in_month[2] = 29;
		return TRUE;
	}
	else
	{
		days_in_month[2] = 28;
		return FALSE;
	}
}

void calendar(int year, int daycode)
{
	int month, day;
	for ( month = 1; month <= 12; month++ )
	{
		printf("%s", months[month]);
		printf("\n\nSun  Mon  Tue  Wed  Thu  Fri  Sat\n" );
		for ( day = 1; day <= 1 + daycode * 5; day++ )
		{
			printf(" ");
		}
		for ( day = 1; day <= days_in_month[month]; day++ )
		{
			printf("%2d", day );
			if ( ( day + daycode ) % 7 > 0 )
				printf("   " );
			else
				printf("\n " );
		}
			daycode = ( daycode + days_in_month[month] ) % 7;
	}
}

struct Date 
{
    int dd;
    int mm;
    int yy;
};

struct Date date;

struct Remainder 
{
    int dd;
    int mm;
    char note[50];
};

struct Remainder R;

void print_date(int mm, int yy) 
{
    printf("---------------------------\n");
    printf("%d , %d", mm, yy);
    printf("\n---------------------------\n");
}

int check_leapYear(int year) 
{
    if (year % 400 == 0 || (year % 100 != 0 && year % 4 == 0))
        return 1;
    return 0;
}

int getNumberOfDays(int month, int year) 
{
    switch (month) 
    {
        case 1: return 31;
        case 2: return check_leapYear(year) ? 29 : 28;
        case 3: return 31;
        case 4: return 30;
        case 5: return 31;
        case 6: return 30;
        case 7: return 31;
        case 8: return 31;
        case 9: return 30;
        case 10: return 31;
        case 11: return 30;
        case 12: return 31;
        default: return -1;
    }
}

char *getName(int day) 
{
    switch (day) 
    {
        case 0: return "Sunday";
        case 1: return "Monday";
        case 2: return "Tuesday";
        case 3: return "Wednesday";
        case 4: return "Thursday";
        case 5: return "Friday";
        case 6: return "Saturday";
        default: return "Error in getName() module. Invalid argument passed";
    }
}

int getDayNumber(int day, int mon, int year) 
{
    int res = 0, t1, t2, y = year;
    year = year - 1600;
    while (year >= 100) 
    {
        res = res + 5;
        year = year - 100;
    }
    res = (res % 7);
    t1 = ((year - 1) / 4);
    t2 = (year - 1) - t1;
    t1 = (t1 * 2) + t2;
    t1 = (t1 % 7);
    res = res + t1;
    res = res % 7;
    t2 = 0;
    for (t1 = 1; t1 < mon; t1++) 
    {
        t2 += getNumberOfDays(t1, y);
    }
    t2 = t2 + day;
    t2 = t2 % 7;
    res = res + t2;
    res = res % 7;
    if (y > 2000)
        res = res + 1;
    res = res % 7;
    return res;
}

char *getDay(int dd, int mm, int yy) 
{
    int day;
    if (!(mm >= 1 && mm <= 12)) 
    {
        return "Invalid month value";
    }
    if (!(dd >= 1 && dd <= getNumberOfDays(mm, yy))) 
    {
        return "Invalid date";
    }
    if (yy >= 1600) 
    {
        day = getDayNumber(dd, mm, yy);
        day = day % 7;
        return getName(day);
    }
    else
    {
        return "Please give year more than 1600";
    }
}

int checkNote(int dd, int mm) 
{
    FILE *fp;
    fp = fopen("note.dat", "rb");
    if (fp == NULL) 
    {
        printf("Error in Opening the file");
    }
    while (fread(&R, sizeof(R), 1, fp) == 1) 
    {
        if (R.dd == dd && R.mm == mm) 
        {
            fclose(fp);
            return 1;
        }
    }
    fclose(fp);
    return 0;
}

void printMonth(int mon, int year)
{
    int nod, day, cnt, d = 1;
    nod = getNumberOfDays(mon, year);
    day = getDayNumber(d, mon, year);
    printf("\n%s, %d\n", mon == 1 ? "January" : mon == 2 ? "February" : mon == 3 ? "March" : mon == 4 ? "April" : mon == 5 ? "May" : mon == 6 ? "June" : mon == 7 ? "July" : mon == 8 ? "August" : mon == 9 ? "September" : mon == 10 ? "October" : mon == 11 ? "November" : "December", year);
    printf("Sun Mon Tue Wed Thu Fri Sat\n");
    for (int i = 0; i < day; i++) 
    {
        printf("    ");
        cnt++;
    }
    for (int i = 1; i <= nod; i++) 
    {
        if (cnt % 7 == 0) 
        {
            printf("\n");
            cnt = 0;
        }
        printf("%3d ", i);
        cnt++;
    }
    printf("\n\n");
}

void AddNote()
{
    FILE *fp;
    fp = fopen("note.dat", "ab+");
    if (fp == NULL) 
    {
        printf("Error in Opening the file");
        return;
    }
    printf("Enter the date (DD MM): ");
    scanf("%d%d", &R.dd, &R.mm);
    printf("Enter the Note (50 characters max): ");
    scanf(" %[^\n]", R.note);
    if (fwrite(&R, sizeof(R), 1, fp)) 
    {
        printf("Note is saved successfully\n");
    }
    else
    {
        printf("\aFailed to save!!\n");
    }
    fclose(fp);
}

void showNote() 
{
    FILE *fp;
    int i = 0, isFound = 0;
    fp = fopen("note.dat", "rb");
    if (fp == NULL) 
    {
        printf("Error in opening the file\n");
        return;
    }
    printf("Enter the month (MM): ");
    scanf("%d", &R.mm);
    while (fread(&R, sizeof(R), 1, fp) == 1) 
    {
        if (R.mm == date.mm) 
        {
            printf("Note %d Day = %d: %s\n", i + 1, R.dd, R.note);
            isFound = 1;
            i++;
        }
    }
    if (isFound == 0) 
    {
        printf("This Month contains no note\n");
    }
    fclose(fp);
}

int main() 
{
    int choice;
    while (1) 
    {
        printf("1. Print year Calender\n");
        printf("2. Print all the days of a month\n");
        printf("3. Find Out the Day\n");
        printf("4. Add Note\n");
        printf("5. Show Notes\n");
        printf("6. EXIT\n");
        printf("ENTER YOUR CHOICE: ");
        scanf("%d", &choice);

        switch (choice) 
        {
            case 1:
                int year, daycode, leapyear;
	            year = inputyear();
	            daycode = determinedaycode(year);
	            determineleapyear(year);
	            calendar(year, daycode);
            	printf("\n");
            	break;
        
            case 2:
                printf("Enter month and year (MM YYYY): ");
                scanf("%d %d", &date.mm, &date.yy);
                printMonth(date.mm, date.yy);
                break;
        
            case 3:
                printf("Enter date (DD MM YYYY): ");
                scanf("%d %d %d", &date.dd, &date.mm, &date.yy);
                printf("Day is: %s\n", getDay(date.dd, date.mm, date.yy));
                break;
        
            case 4:
                AddNote();
                break;
        
            case 5:
                showNote();
                break;
        
            case 6:
                exit(0);
        }
    }
    return 0;
}