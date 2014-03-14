for type in bpn prod tina xml
do

  for f in samples/$type/*;
  do
    ./simple $type $f;
  done;

done;
