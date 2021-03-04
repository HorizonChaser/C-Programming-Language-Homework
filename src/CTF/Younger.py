s = 'QWERTYUIOPASDFGHJKLZXCVBNMqwertyuiopasdfghjklzxcvbnm' #off_418000
d = 'TOiZiZtOrYaToUwPnToBsOaOapsyS' #off_418004
f = ''
for i in range(len(d)):
    if i%2 == 0:
        f = f + d[i]
    else:
        if(d[i].isupper()):
            f = f + chr(s.find(d[i])+96)
        else:
            f = f + chr(s.find(d[i])+38)
print(f)