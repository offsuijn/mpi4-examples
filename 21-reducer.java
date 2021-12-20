import java.io.IOException;
import java.util.Iterator;
import org.apache.hadoop.mapred.MapReduceBase;
import org.apache.hadoop.mapred.OutputCollector;
import org.apache.hadoop.mapred.Reducer;
import org.apache.hadoop.mapred.Reporter;
import org.apache.hadoop.io.Text;
import org.apache.hadoop.io.IntWritable;

public class Reducer1 extends MapReduceBase 
							  implements Reducer<IntWritable, IntWritable, IntWritable, Text> {
	
	public void reduce(IntWritable key, Iterator<IntWritable> values, 
	 OutputCollector<IntWritable, Text> output, Reporter reporter) throws IOException {

		int sum = 0;
		int n = 0;
		
		while(values.hasNext()) {
			sum += values.next().get();
			n++;
		}
		
		double avg = (double)sum/(double)n;
		
		if (avg < 2.5)
			output.collect(key, new Text(String.format("%.2f", avg)));
	}
}
