import json
import dateutil.parser
import time  

def counterPair(a, Dates):
    ans =[]
    pair = []
    for i in Dates:
        pair = []
        pair.append(i)
        pair.append(0)
        ans.append(pair) 
    
    for i in range(len(a)):
        for j in range(len(a[i][1])):        
            for k in range(len(ans)):
                x = a[i][1][j]
                y = ans[k][0]
                if x == y:
                    ans[k][1] += 1
    
    pair = []
    for i in range(len(ans)):
        if ans[i][1] != 0:
            pair.append(ans[i])
    ans = pair
    return ans                


with open("c:\\Users\\Cornell\\Google Drive\\vs code\\Hubspot Test\\partners.txt") as f:
    data = json.load(f)

country = []
for i in data["partners"]:
    country.append(i["country"])
country = list(dict.fromkeys(country))
# print(country)

AllDates = []
for i in data["partners"]:
    AllDates.append(i["availableDates"])
AllDates = [j for i in AllDates for j in i]
AllDates = list(dict.fromkeys(AllDates))

pairs = []

for j in range(len(AllDates)-1):
    date1 = dateutil.parser.parse(AllDates[j])
    d1 = date1.strftime("%d")
    date2 = dateutil.parser.parse(AllDates[j+1])
    d2 = date2.strftime("%d")
    if int(d1)+1 == int(d2):
        x = []
        x.append(AllDates[j])
        x.append(AllDates[j+1])
        pairs.append(x)
AllDates = pairs   
# print(AllDates)    



res =  [True for i in range(len(country))]


countryLen = range(len(country))
BigData = []

for i in countryLen:
    check = False
    check2 = False
    for j in range(len(data["partners"])):
        pair = []
        
        if BigData == []:
            pair.append(data["partners"][j]["email"])
            pair.append(data["partners"][j]["availableDates"])
            BigData.append([pair])
            check = True
        
        elif (data["partners"][j]["country"] == country[i]) & check: 
            pair.append(data["partners"][j]["email"])
            pair.append(data["partners"][j]["availableDates"])
            BigData[i] = BigData[i]+ [pair] 
            check2 = True

        elif (data["partners"][j]["country"] != country[i]) & check2:
            pair.append(data["partners"][j]["email"])
            pair.append(data["partners"][j]["availableDates"])
            BigData.append([pair])
            check = False
            check2 = False

        elif data["partners"][j]["country"] != country[i]:
            check = True
    
#print(BigData)
count = 0
for i in countryLen:
    for j in BigData[i]:
        pair = []
        count +=1
        for k in range(len(j[1])-1):
            date1 = dateutil.parser.parse(j[1][k])
            d1 = date1.strftime("%d")
            date2 = dateutil.parser.parse(j[1][k+1])
            d2 = date2.strftime("%d")
            if int(d1)+1 == int(d2):
                x = []
                x.append(j[1][k])
                x.append(j[1][k+1])
                pair.append(x)
        
        j[1] = pair 


print("          ")

answer = {}
answer['Dates'] = []

for z in range(len(country)):
    a = counterPair(BigData[z] , AllDates)
    Max = 0
    date = []
    for i in a:
        if i[1] > Max:
            Max = i[1]
    for i in a:
        if i[1] == Max:
            date.append(i[0])
            date = [j for i in date for j in i]
            break
    avail_email = []
    for i in BigData[z]:
        for j in i[1]:
            if j == date:
                avail_email.append(i[0])
                break

    answer['Dates'].append({
        'Country': country[z],
        'AvailableDate': date,
        'email': avail_email
    })

with open('ans.txt', 'w') as f:
    json.dump(answer,f)   


print(json.dumps(answer, indent=4, sort_keys=True))