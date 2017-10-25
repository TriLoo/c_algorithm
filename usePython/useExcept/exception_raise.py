#encoding=UTF-8

class ShortInputException(Exception):
    '''
    User defined class.
    '''

    def __init__(self, length, atleast):
        Exception.__init__(self)
        self.length = length
        self.atleast = atleast

try:
    text = input('Enter something-->')
    if len(text) < 3:
        raise ShortInputException(len(text), 3)
except ShortInputException as ex:
    print('ShortInputException: The input was ' + '{0} long, except at least {1}'.format(ex.length, ex.atleast))
else:
    print('No exception was raised')

