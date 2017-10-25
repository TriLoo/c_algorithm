def reverse(text):
    '''
    This is a function.

    :param text:
    :return:
    '''
    return text[::-1]

def is_palindrome(text):
    return reverse(text) == text

#try:
something = input('Enter text:')
if is_palindrome(something):
    print('Yes, it is a palindrome')
else:
    print('No, it is not a palindrome')

print('function help : ', reverse.__doc__)

poems = '''
    Programming is fun
    When the work is done
    if you wanna make your work also fun: use Python & C++
'''

f = open('poem.txt', 'w')
f.write(poems)
f.close()

f = open('poem.txt', 'r')
while True:
    line = f.readline()
    if len(line) == 0:
        break;
    print(line, end=' ')
else:
    print('Read finished.')

f.close()


