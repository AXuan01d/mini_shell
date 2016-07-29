make clean

make
echo "\n**********test_write**************"
echo "cat in.txt"
cat in.txt
echo -e "./test_read  in.txt  "
./test_read  in.txt  
echo -e '\n'

echo "**********test_write**************"
echo -e "./test_write  out.txt  sssssdddd"
./test_write  out.txt  sssssdddd

echo -e "cat out.txt"
cat out.txt 
echo -e '\n\n'


echo "**********test_append**************"
echo -e "./test_append  out.txt  qweqweqweq"
./test_append  out.txt  qweqweqweq

echo -e "cat out.txt"
cat out.txt 
echo -e '\n'



