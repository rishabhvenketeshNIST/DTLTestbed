double average(List<Double> data) {
  if(data.size() == 0) return 0;
  double total = 0;
  for(double d : data) {
    total += d;
  }
  return total/data.size();
}

double percentile(List<Double> data, double perc01) {
  int size = data.size();
  if(size == 0) return 0;
  ArrayList<Double> copy = new ArrayList<>(data);
  Collections.sort(copy);
  double target = (size-1)*Math.max(Math.min(perc01, 1), 0);
  int left = Math.max((int) target, 0);
  int right = Math.min((int) (target+1), size-1);
  double rightweight = (target%1.0);
  double leftweight = 1-rightweight;
  return copy.get(left)*leftweight+copy.get(right)*rightweight;
}

double median(List<Double> data) {
  if(data.size() == 0) return 0;
  ArrayList<Double> copy = new ArrayList<>(data);
  Collections.sort(copy);
  if(copy.size() % 2 == 0) {
    return (copy.get(copy.size()/2) + copy.get(copy.size()/2-1))*0.5;
  } else {
    return copy.get(copy.size()/2);
  }
}

double variance(List<Double> data) {
  double N = data.size();
  if(N == 0) return 0;
  double mean = average(data);
  double sse = 0;
  for(double d : data) {
    sse += (d - mean)*(d - mean);
  }
  return sse/(N-1);
}

double max(List<Double> data) {
  if(data.size() == 0) return 0;
  double largest = Double.NEGATIVE_INFINITY;
  for(double d : data) {
    if (d > largest) largest = d;
  }
  return largest;
}

double min(List<Double> data) {
  if(data.size() == 0) return 0;
  double smallest = Double.POSITIVE_INFINITY;
  for(double d : data) {
    if (d < smallest) smallest = d;
  }
  return smallest;
}
