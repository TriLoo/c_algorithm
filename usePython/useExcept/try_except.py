try:
    text = input('Enter something -->')
except EOFError:
    print('why did you do an EOF on me?')
except KeyboardInterrupt:
    print('You cancelled the operation.')
else:
    print('U entered {}'.format(text))



