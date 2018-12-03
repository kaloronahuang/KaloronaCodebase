import sys
expre = input()
expre = expre.replace("^", "**")
left = expre.count("(")
right = expre.count(")")
if left > right:
    for i in range(0, left-right):
        expre = expre + ")"
else:
    for i in range(0, right-left):
        expre = "(" + expre
print(int(eval(expre)))
