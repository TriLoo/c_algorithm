import sys
import time

''' use try ... finally
f = None
try:
    f = open('poem.txt')
    while True:
        line = f.readline()
        if len(line) == 0:
            break;
        print(line, end = ' ')
        sys.stdout.flush()
        print('Press ctrl+c now')
        time.sleep(2)
except IOError:
    print('could not find file poem.txt')
except KeyboardInterrupt:
    print('You have cancelled the reading from the file.')
finally:
    if f:
        f.close()
    print("Cleaning up: Closed the file")

'''

# use with
with open('poems.txt') as f:
    for line in f:
        print(line, end=' ')

