# -*- coding: utf-8 -*-

# \author smh
# \date 2019.08.16
# \brief random generate a team name

import random
from random import randint
import string


def fisher_yates_shuffle(str_list):
    list_range = range(0, len(str_list))
    if not isinstance(str_list, list):
        str_list = list(str_list)
    for i in list_range:
        j = randint(list_range[0], list_range[-1])
        str_list[i], str_list[j] = str_list[j], str_list[i]
    return ''.join(str_list)


def randomString(str_length, mode, can_repeat=True, letters=None):
    if mode == 'lowercase':
        letters = string.ascii_lowercase
    elif mode == 'bothcase':
        letters = string.ascii_letters
    elif mode == 'specific':
        assert letters is not None
    elif mode == 'nums':
        letters = string.ascii_letters +string.digits
    elif mode == 'all':
        letters = string.ascii_letters + string.digits + string.punctuation
    else:
        print('Not implemented.')

    if can_repeat:
        return ''.join(random.choice(letters) for i in range(str_length))
    else:
        assert len(letters) >= str_length
        return ''.join(random.sample(letters, str_length))


if __name__ == '__main__':
    str_len = 7
    mode = 'bothcase'

    team_name = randomString(str_len, mode)
    print('name before shuffle: ', team_name)
    random_name = fisher_yates_shuffle(team_name)
    print('name after shuffle: ', random_name)
