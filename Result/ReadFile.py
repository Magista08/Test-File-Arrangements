import csv
import os
from os.path import basename
from email.mime.text import MIMEText
from email.mime.multipart import MIMEMultipart
from email.mime.application import MIMEApplication



def main():
    LogFile_4 = open("FileArrangeMent_262144_4layer_10000.log")
    LogFile_8 = open("FileArrangeMent_262144_8layer_10000.log")
    LogFile_64 = open("FileArrangeMent_262144_64layer_10000.log")
    LogFile_512 = open("FileArrangeMent_262144_512layer_10000.log")
    #LogFile_262144 = open("FileArrangeMent_262144_262144layer_10000.log")
    output_dict = {4: [], 8: [], 64: [], 512: [], 262144: []}
    for i in LogFile_4:
        temp_list = i.split()
        if len(temp_list) == 0:
            continue
        if ((temp_list[-1][-1].isdigit())
                and (temp_list[-1][0] == "i")):
            get_int = temp_list[-1].split(":")
            num = float(get_int[-1])
            output_dict[4].append(num)
        elif temp_list[-1][-1].isdigit():
            num = float(temp_list[-1])
            output_dict[4].append(num)

    for i in LogFile_8:
        temp_list = i.split()
        if len(temp_list) == 0:
            continue
        if ((temp_list[-1][-1].isdigit())
                and (temp_list[-1][0] == "i")):
            get_int = temp_list[-1].split(":")
            num = float(get_int[-1])
            output_dict[8].append(num)
        elif temp_list[-1][-1].isdigit():
            num = float(temp_list[-1])
            output_dict[8].append(num)

    for i in LogFile_64:
        temp_list = i.split()
        if len(temp_list) == 0:
            continue
        if ((temp_list[-1][-1].isdigit())
                and (temp_list[-1][0] == "i")):
            get_int = temp_list[-1].split(":")
            num = float(get_int[-1])
            output_dict[64].append(num)
        elif temp_list[-1][-1].isdigit():
            num = float(temp_list[-1])
            output_dict[64].append(num)

    for i in LogFile_512:
        temp_list = i.split()
        if len(temp_list) == 0:
            continue
        if ((temp_list[-1][-1].isdigit())
                and (temp_list[-1][0] == "i")):
            get_int = temp_list[-1].split(":")
            num = float(get_int[-1])
            output_dict[512].append(num)
        elif temp_list[-1][-1].isdigit():
            num = float(temp_list[-1])
            output_dict[512].append(num)
    '''
    for i in LogFile_262144:
        temp_list = i.split()
        if len(temp_list) == 0:
            continue
        if ((temp_list[-1][-1].isdigit())
                and (temp_list[-1][0] == "i")):
            get_int = temp_list[-1].split(":")
            num = float(get_int[-1])
            output_dict[262144].append(num)
        elif temp_list[-1][-1].isdigit():
            num = float(temp_list[-1])
            output_dict[262144].append(num)
    '''


    print(output_dict)

    DataList = list()
    heading_list_1 = ["Files in every Layer"]
    for i in output_dict.keys():
        heading_list_1.append(i)
    DataList.append(heading_list_1)
    heading_list_2 = ["Layer", 9, 6, 3, 2, 1]
    DataList.append(heading_list_2)
    for i in range(len(output_dict[4])):
        temp_list = list()
        temp_list.append(i)
        temp_list.append(output_dict[4][i])
        if i < len(output_dict[8]):
            temp_list.append(output_dict[8][i])
        if i < len(output_dict[64]):
            temp_list.append(output_dict[64][i])
        if i < len(output_dict[512]):
            temp_list.append(output_dict[512][i])
        if i < len(output_dict[262144]):
            temp_list.append(output_dict[262144][i])
        DataList.append(temp_list)

    '''
    DataList = list()
    heading_list_1 = ["Files in every sub folders", "Layers"]
    for i in range(len(output_dict[4])):
        heading_list_1.append(i)
    DataList.append(heading_list_1)
    compare_dict = {4: 9, 8: 6, 64: 3, 512: 2, 262144: 1}
    for i in list(output_dict.keys()):
        data_list_1 = output_dict[i].copy()
        data_list_1.insert(0, compare_dict[i])
        data_list_1.insert(0, i)
        DataList.append(data_list_1)
    '''
    LogFile_csvfile = open("10000level.csv", "w", newline='')
    LogCSVwrite = csv.writer(LogFile_csvfile)
    LogCSVwrite.writerows(DataList)

main()
