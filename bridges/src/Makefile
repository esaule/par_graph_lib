STYLE_PARAMS = -A2 -T4 -xn -xc -xV -C -S -N -xU  -Y -p -xg -H -y -xb

ALL_TARGETS = ds array element sle dle csle cdle mle tree bintree bst avl gral gram  edge\
				elvis linkvis bridges scomm color

ast:
	astyle $(STYLE_PARAMS) tmp.cpp

ds:
	astyle $(STYLE_PARAMS) DataStructure.h
array:
	astyle $(STYLE_PARAMS) Array.h
element:
	astyle $(STYLE_PARAMS) Element.h
sle:
	astyle $(STYLE_PARAMS) SLelement.h
mle:
	astyle $(STYLE_PARAMS) MLelement.h
dle:
	astyle $(STYLE_PARAMS) DLelement.h
csle:
	astyle $(STYLE_PARAMS) CircSLelement.h
cdle:
	astyle $(STYLE_PARAMS) CircDLelement.h
tree:
	astyle $(STYLE_PARAMS) TreeElement.h
bintree:
	astyle $(STYLE_PARAMS) BinTreeElement.h
bst:
	astyle $(STYLE_PARAMS) BSTElement.h
avl:
	astyle $(STYLE_PARAMS) AVLTreeElement.h
gral:
	astyle $(STYLE_PARAMS) GraphAdjList.h
gram:
	astyle $(STYLE_PARAMS) GraphAdjMatrix.h
edge:
	astyle $(STYLE_PARAMS) Edge.h
elvis:
	astyle $(STYLE_PARAMS) ElementVisualizer.h
linkvis:
	astyle $(STYLE_PARAMS) LinkVisualizer.h
bridges:
	astyle $(STYLE_PARAMS) Bridges.h
scomm:
	astyle $(STYLE_PARAMS) ServerComm.h
color:
	astyle $(STYLE_PARAMS) Color.h
dsrc:
	astyle $(STYLE_PARAMS) DataSource.h

# data source dependent
game:
	astyle $(STYLE_PARAMS) data_src/Game.h
gutenberg:
	astyle $(STYLE_PARAMS) data_src/GutenbergBook.h
shakespeare:
	astyle $(STYLE_PARAMS) data_src/Shakespeare.h
eq:
	astyle $(STYLE_PARAMS) data_src/EarthquakeUSGS.h

all:
	make $(ALL_TARGETS)
	



