import gspread
import streamlit as st
gc = gspread.service_account(filename='farmmonitoring-5b63e966216f.json')
wks = gc.open("Farm_Monitoring").sheet1

all_values = wks.get_all_values()

column_values = wks.row_values(1)
print("Column Name : ", column_values)
# Get the last row of data
last_row = all_values[-1]
dict1 = {}
for i in range(0, len(last_row)):
    dict1[column_values[i]] = last_row[i]


print(dict1)
# Print the last row to the console
print("Last row of data:", last_row)