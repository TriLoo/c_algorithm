with open("./timemachine.txt") as f:
    time_machine = f.read()
print(time_machine[0:500])

time_machine = time_machine.lower().replace('\n', ' ').replace('\r', ' ')

character_list = list(set(time_machine))
character_dict = dict([(char, i) for i, char in enumerate(character_list)])

vocab_size = len(character_dict)

time_numerical = [character_dict[char] for char in time_machine]
sample = time_numerical[:40]

print('sample = ', sample)

