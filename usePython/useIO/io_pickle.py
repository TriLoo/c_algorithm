import pickle

shoplistfile = 'shoplist.data'
shoplist = ['apple', 'mango', 'carrot']     # list

f = open(shoplistfile, 'wb')
pickle.dump(shoplist, f)

f.close()

del shoplist

f = open(shoplistfile, 'rb')
#load the object from the file
storedlist = pickle.load(f)
print(storedlist)