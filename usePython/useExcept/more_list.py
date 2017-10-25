listone = [2, 3, 4]
listtwo = [2 * i for i in listone if i > 3]
print(listtwo)

def powersum(power, *args):
    '''
    Return the sum of each argument raised to the specified power.
    :param power:
    :param args:
    :return:
    '''

    total = 0
    for i in args:
        total += pow(i, power)
    return total

print(powersum.__doc__)
print(powersum(2, 3, 4))