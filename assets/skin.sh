#!/usr/bin/bash

# Example:
#
# gunner   - `./assets/skin.sh POSS gunner no "E F" "M N O P Q R T U"`
# player   - `./assets/skin.sh PLAY player yes "E F G" "O P Q R S T U V W"`

PREFIX="$1"
NAME="$2"
FLIP="$3"
SHOOT="$4"
DEATH="$5"

if [[ $PREFIX == "" || $NAME == "" || $FLIP == "" || $SHOOT == "" || $DEATH == "" ]]; then
	echo "Missing argument"
	exit 1
fi

mkdir -p assets/$NAME

conv()
{
	convert -flop $1 $2.png
	convert $2.png $2 # -flip
	rm $2.png
}

if [[ $FLIP == "yes" ]]; then
	for i in A B C D $SHOOT
	do
		mkdir -p assets/$NAME/$i

		cp assets/textures/$PREFIX${i}1.tga assets/$NAME/$i/$PREFIX${i}1.tga
		cp assets/textures/$PREFIX${i}5.tga assets/$NAME/$i/$PREFIX${i}5.tga

		conv assets/textures/$PREFIX${i}2${i}8.tga assets/$NAME/$i/$PREFIX${i}8.tga
		cp assets/textures/$PREFIX${i}2${i}8.tga assets/$NAME/$i/$PREFIX${i}2.tga

		conv assets/textures/$PREFIX${i}3${i}7.tga assets/$NAME/$i/$PREFIX${i}7.tga
		cp assets/textures/$PREFIX${i}3${i}7.tga assets/$NAME/$i/$PREFIX${i}3.tga

		conv assets/textures/$PREFIX${i}4${i}6.tga assets/$NAME/$i/$PREFIX${i}6.tga
		cp assets/textures/$PREFIX${i}4${i}6.tga assets/$NAME/$i/$PREFIX${i}4.tga
	done
else
	for i in A B C D $SHOOT
	do
		mkdir -p assets/$NAME/$i

		cp assets/textures/$PREFIX${i}1.tga assets/$NAME/$i/$PREFIX${i}1.tga
		cp assets/textures/$PREFIX${i}2.tga assets/$NAME/$i/$PREFIX${i}2.tga
		cp assets/textures/$PREFIX${i}3.tga assets/$NAME/$i/$PREFIX${i}3.tga
		cp assets/textures/$PREFIX${i}4.tga assets/$NAME/$i/$PREFIX${i}4.tga
		cp assets/textures/$PREFIX${i}5.tga assets/$NAME/$i/$PREFIX${i}5.tga
		cp assets/textures/$PREFIX${i}6.tga assets/$NAME/$i/$PREFIX${i}6.tga
		cp assets/textures/$PREFIX${i}7.tga assets/$NAME/$i/$PREFIX${i}7.tga
		cp assets/textures/$PREFIX${i}8.tga assets/$NAME/$i/$PREFIX${i}8.tga
	done
fi

INDEX=0
for i in $DEATH
do
	cp assets/textures/$PREFIX${i}0.tga assets/$NAME/${PREFIX}DEA$INDEX.tga
	INDEX=$(($INDEX + 1))
done
