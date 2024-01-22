
/*
* Program: Read CSV File Data To An Array Of Structs
*/
/*
 1. Assume you are receiving a data in CSV format “#123456UNI,123.456, 342.785, E,
12.5, 34.6, 01,01,983,01:23:34,AM,H# over the UART onto a buffer, Write a function to
parse this data and store the values in a structure. Please note in the above data in the
format as below
#<CustomerID>,<Latitude>,<Longitude>,<Direction>,<AccelerometerX>,<AccelerometerY>,<Da
y>,<Month>,<Year>,<Time in HH:MM:SS>,<AM/PM>,<A/H>#, where A represents that the data
is current data and H represents the data is History data.

 */
#include <stdio.h>

typedef struct
{

  int customerID;
  float latitude;
  float longitude;
  char direction;
  float accelerometer_x;
  float accelerometer_y;
  int day;
  int month;
  int year;
  char time[10];
  char meridiem[5];
  char data_type;
} Customer;

int main(void)
{
  // file pointer variable for accessing the file
  FILE *file;

  // opening csv file in read mode
  file = fopen("csv_data.txt", "r");

  //Checking for errors while opening the file.
  if (file == NULL)
  {
    printf("Error in opening file.\n");
    return 1;
  }

  // array of structs for storing the data from the file
  Customer customers[100];

  int read = 0;
  int index = 0;

  // read all index from the file and store them into the customer array
  do
  {
    read = fscanf(file,
                  "%d,%f,%f,%c,%f,%f,%d,%d,%d,%9[^,],%4[^,],%c",
                  &customers[index].customerID,
				  &customers[index].latitude,
				  &customers[index].longitude,
				  &customers[index].direction,
				  &customers[index].accelerometer_x,
				  &customers[index].accelerometer_y,
				  &customers[index].day,
				  &customers[index].month,
				  &customers[index].year,
				  customers[index].time,
				  customers[index].meridiem,
				  &customers[index].data_type);


    // if there was an error reading from the file exit with an error message
    // and status
    if (ferror(file))
    {
      printf("Error reading file.\n");
      return 1;
    }

  } while (!feof(file));


  fclose(file);

  // print out each values of structure that was read
    printf("%d,%f,%f,%c,%f,%f,%d,%d,%d,%s,%s,%c",
    		  &customers[0].customerID,
			  &customers[0].latitude,
			  &customers[0].longitude,
			  &customers[0].direction,
			  &customers[0].accelerometer_x,
			  &customers[0].accelerometer_y,
			  &customers[0].day,
			  &customers[0].month,
			  &customers[0].year,
			  customers[0].time,
			  customers[0].meridiem,
			  &customers[0].data_type);
  printf("\n");

  return 0;
}
