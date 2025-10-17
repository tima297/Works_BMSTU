#include <iostream>
#include <vector>
#include <algorithm> 
#include <numeric>
using namespace std;

int main() {
	// задание 1

	vector<int> numbers(10);
	cout << "Write 10 numbers:" << endl;
	for (int i = 0; i < 10; i++) {
		cin >> numbers[i];
	};
	cout << "numbers:";
	for_each(numbers.begin(), numbers.end(), [](int x) {cout << x << " "; });

	 // задание 2 

	vector<int> numbers(10);
	cout << "Write 10 numbers:" << endl;
	for (int i = 0; i < 10; i++) {
		cin >> numbers[i];
	};
	cout << "numbers:";
	for_each(numbers.begin(), numbers.end(), [](int x) {cout << x*2 << " "; });

	// задание 3
	 
	vector<int> numbers(20);
	cout << "Write 20 numbers:" << endl;
	for (int i = 0; i < 20; i++) {
		cin >> numbers[i];
	};
	cout << "numbers:";
	for_each(numbers.begin(), numbers.end(), [](int x) {cout << x  << " "; });
	cout << " " << endl;
	auto max_it = max_element(numbers.begin(), numbers.end());
	auto min_it  = min_element(numbers.begin(), numbers.end());
	cout << "The maximum:" << *max_it << endl;
	cout << "The minimum:" << *min_it << endl;

	// задание 4

	vector<int> numbers(20);
	cout << "Write 20 numbers:" << endl;
	for (int i = 0; i < 20; i++) {
		cin >> numbers[i];
	};
	cout << "numbers:";
	for_each(numbers.begin(), numbers.end(), [](int x) {cout << x << " "; });
	auto pluse = remove_if(numbers.begin(), numbers.end(), [](int x){return x < 0; });
	numbers .erase(pluse, numbers.end());
	cout << "The new vector: ";
	for (int x : numbers) cout << x << " ";


	// задание 5

	vector<int> numbers(20);
	cout << "Write 20 numbers:" << endl;
	for (int i = 0; i < 20; i++) {
		cin >> numbers[i];
	};
	cout << "numbers:";
	for_each(numbers.begin(), numbers.end(), [](int x) {cout << x  << " "; });
	cout << " " << endl;
	auto max_it = max_element(numbers.begin(), numbers.end());
	auto min_it  = min_element(numbers.begin(), numbers.end());
	cout << "The maximum:" << *max_it << endl;
	cout << "The minimum:" << *min_it << endl;
	double total = accumulate(numbers.begin(), numbers.end(), 0.0);
	cout << "Summ of numbers: " << total << "\n";
	sort(numbers.begin(), numbers.end()); 
	for (int x : numbers) cout << x << " ";

	vector<int> sorted_numbers = numbers;

	sort(sorted_numbers.begin(), sorted_numbers.end());

	double median;
	size_t n = sorted_numbers.size();
		median = (sorted_numbers[n / 2 - 1] + sorted_numbers[n / 2]) / 2.0;
		cout << "Mediana: " << median << endl;



    // задание 6

	vector<int> numbers(20);
	cout << "Write 20 numbers:" << endl;
	for (int i = 0; i < 20; i++) {
		cin >> numbers[i];
	};
	cout << "numbers:";
	for_each(numbers.begin(), numbers.end(), [](int x) {cout << x << " "; });
	auto it = find(numbers.begin(), numbers.end(), 7);
	if (it != numbers.end())
		cout << "Element found: " << *it << " on position " << (it - numbers.begin()) <<
		"\n";
	else
		cout << "Element didn't find\n";

	sort(numbers.begin(), numbers.end());
	auto last = unique(numbers.begin(), numbers.end());
	numbers.erase(last, numbers.end());
	for (int x : numbers) cout << x << " ";

	
	// задание 7

	vector<int> numbers(10);
	cout << "Write 10 numbers of temperature:" << endl;
	for (int i = 0; i < 10; i++) {
		cin >> numbers[i];
	};
	cout << "numbers: ";
	for_each(numbers.begin(), numbers.end(), [](int x) {cout << x << " "; });
	auto pluse = remove_if(numbers.begin(), numbers.end(), [](int x) {return x < -50 || x > 50 ; });
	numbers.erase(pluse, numbers.end());
	cout << " " << endl;
	cout << "Temperature from -50 to 50 degrees: ";
	for (int x : numbers) cout << x << " ";
	cout << " " << endl;
	auto max_it = max_element(numbers.begin(), numbers.end());
	auto min_it = min_element(numbers.begin(), numbers.end());
	cout << "The maximum:" << *max_it << endl;
	cout << "The minimum:" << *min_it << endl;
	double sum = accumulate(numbers.begin(), numbers.end(), 0);
	cout << "The average " << sum/2 << "\n";
	bool more_than_10 = all_of(numbers.begin(), numbers.end(),
		[](double temp) { return temp > -10.0; });
	if (more_than_10) {
		cout << "Yes, all numbers are more than -10°C" << endl;
	}
	else {
		cout << " No, not all of the numbers are more than -10°C" << endl;
	}


	// задание 8

	vector<int> numbers(50);
	cout << "Write 50 numbers of speed of your car" << endl;
	for (int i = 0; i < 50; i++) {
		cin >> numbers[i];
	};
	cout << "Numbers of speed: ";
	for_each(numbers.begin(), numbers.end(), [](int x) {cout << x << " "; });
	auto pluse = remove_if(numbers.begin(), numbers.end(), [](int x) {return x>120 ; });
	numbers.erase(pluse, numbers.end());
	cout << " " << endl;
	cout << "The speed under 120: ";
	for (int x : numbers) cout << x << " ";
	cout << " " << endl;
	double sum = accumulate(numbers.begin(), numbers.end(), 0);
	cout << "The average speed: " << sum / 2 << "\n";
	bool more_than_0 = all_of(numbers.begin(), numbers.end(),
		[](double temp) { return temp > 0; });
	if (more_than_0) {
		cout << "Yes our racer moving all time" << endl;
	}
	else {
		cout << "No, our racer moving not all time" << endl;
	}
	sort(numbers.begin(), numbers.end());



	cout << "10 biggest numbers of speed ";
	for (int x : numbers) cout << x << " ";
	cout << "\n";


	// задание 9


	vector<int> numbers(20);
	cout << "Write 20 numbers of power of your engine in Kwatt" << endl;
	for (int i = 0; i < 20; i++) {
		cin >> numbers[i];
	};
	cout << "Numbers of power of your engine: ";
	for_each(numbers.begin(), numbers.end(), [](int x) {cout << x << " "; });
	auto pluse = remove_if(numbers.begin(), numbers.end(), [](int x) {return x < 0; });
	numbers.erase(pluse, numbers.end());
	cout << " " << endl;
	cout << "The number of power without errors: ";
	for (int x : numbers) cout << x << " ";
	cout << " " << endl;
	double sum = accumulate(numbers.begin(), numbers.end(), 0);
	cout << "The average power: " << sum / 2 << "\n";
	bool more_than_0 = all_of(numbers.begin(), numbers.end(),
		[](double temp) { return temp > 10 && temp < 90; });
	if (more_than_0) {
		cout << "Yes, all your numbers lies in diaposon from 10 to 90  " << endl;
	}
	else {
		cout << "No, not all your numbers lies in diaposon from 10 to 90 " << endl;
	}
	vector<int> sorted_numbers = numbers;
	sort(sorted_numbers.begin(), sorted_numbers.end());
	cout << " " << endl;
	for (int x : sorted_numbers) cout << x << " ";
	double median;
	size_t n = sorted_numbers.size();
	median = (sorted_numbers[n / 2 - 1] + sorted_numbers[n / 2]) / 2.0;
	cout << "Mediana: " << median << endl;


	// задание 10

	vector<double> energy(30);
	cout << "Write 30 numbers of energy consumption in kWh for each day" << endl;
	for (int i = 0; i < 30; i++) {
		cin >> energy[i];
	};

	cout << "Energy consumption for 30 days: ";
	for_each(energy.begin(), energy.end(), [](double x) {cout << x << " "; });

	double total = accumulate(energy.begin(), energy.end(), 0.0);
	cout << " " << endl;
	cout << "Total monthly consumption: " << total << " kWh" << endl;

	double average = total / 30;
	cout << "Average daily consumption: " << average << " kWh" << endl;

	auto minmax = minmax_element(energy.begin(), energy.end());
	cout << "Min consumption day: " << *minmax.first << " kWh" << endl;
	cout << "Max consumption day: " << *minmax.second << " kWh" << endl;

	double threshold = average * 1.2;
	vector<double> peak_days;
	copy_if(energy.begin(), energy.end(), back_inserter(peak_days),[threshold](double x) { return x > threshold; });

	cout << "Peak days (>20% above average): ";
	for_each(peak_days.begin(), peak_days.end(), [](double x) {cout << x << " "; });


	// задание 11 

	vector<double> vibration(50);
	cout << "Write 50 vibration amplitude values" << endl;
	for (int i = 0; i < 50; i++) {
		cin >> vibration[i];
	};

	cout << "Original vibration amplitudes: ";
	for_each(vibration.begin(), vibration.end(), [](double x) {cout << x << " "; });

	auto noise = remove_if(vibration.begin(), vibration.end(), [](double x) {return x < 0.1; });
	vibration.erase(noise, vibration.end());
	cout << " " << endl;
	cout << "Vibration without noise (<0.1): ";
	for (double x : vibration) cout << x << " ";

	double avg_vibration = accumulate(vibration.begin(), vibration.end(), 0.0) / vibration.size();
	double max_vibration = *max_element(vibration.begin(), vibration.end());
	cout << " " << endl;
	cout << "Average vibration: " << avg_vibration << endl;
	cout << "Max vibration: " << max_vibration << endl;

	bool all_above_threshold = all_of(vibration.begin(), vibration.end(),
		[](double x) { return x > 0.5; });
	if (all_above_threshold) {
		cout << "Yes, all values exceed 0.5 threshold" << endl;
	}
	else {
		cout << "No, not all values exceed 0.5 threshold" << endl;
	}

	vector<double> sorted_vibration = vibration;
	sort(sorted_vibration.begin(), sorted_vibration.end(), greater<double>());
	cout << "Top 10 amplitudes: ";
	for (int i = 0; i < min(10, (int)sorted_vibration.size()); i++) {
		cout << sorted_vibration[i] << " ";
	}


	// задание 12
	vector<double> fuel_level(50);
	cout << "Write 50 fuel level measurements (every 10 minutes)" << endl;
	for (int i = 0; i < 50; i++) {
		cin >> fuel_level[i];
	};

	cout << "Fuel level measurements: ";
	for_each(fuel_level.begin(), fuel_level.end(), [](double x) {cout << x << " "; });

	double min_fuel = *min_element(fuel_level.begin(), fuel_level.end());
	double max_fuel = *max_element(fuel_level.begin(), fuel_level.end());
	cout << " " << endl;
	cout << "Minimum fuel level: " << min_fuel << endl;

	double critical_level = max_fuel * 0.05;
	bool below_critical = any_of(fuel_level.begin(), fuel_level.end(),
		[critical_level](double x) { return x < critical_level; });

	if (below_critical) {
		cout << "Warning: fuel level dropped below 5% of maximum!" << endl;
	}
	else {
		cout << "Fuel level never dropped below 5% of maximum" << endl;
	}

	double power_energy = fuel_level[0] - fuel_level[49];
	cout << "Average consumption: " << power_energy / 50 << " per 10 minutes" << endl;

	vector<double> sorted_fuel = fuel_level;
	sort(sorted_fuel.begin(), sorted_fuel.end());
	double median;
	int n = sorted_fuel.size();
	if (n % 2 == 0) {
		median = (sorted_fuel[n / 2 - 1] + sorted_fuel[n / 2]) / 2.0;
	}
	else {
		median = sorted_fuel[n / 2];
	}
	cout << "Median fuel level: " << median << endl;
	
	// задание 13 
		vector<double> pressure(50);
		cout << "Write 50 pressure measurements (1-10 bar)" << endl;
		for (int i = 0; i < 50; i++) {
			cin >> pressure[i];
		};

		cout << "Original pressure measurements: ";
		for_each(pressure.begin(), pressure.end(), [](double x) {cout << x << " "; });

		auto error = remove_if(pressure.begin(), pressure.end(),
			[](double x) {return x < 0 || x > 12; });
		pressure.erase(error, pressure.end());
		cout << " " << endl;
		cout << "Pressure without errors (<0 or >12): ";
		for (double x : pressure) cout << x << " ";

		double avg_pressure = accumulate(pressure.begin(), pressure.end(), 0.0) / pressure.size();
		auto minmax_pressure = minmax_element(pressure.begin(), pressure.end());
		cout << " " << endl;
		cout << "Average pressure: " << avg_pressure << " bar" << endl;
		cout << "Min pressure: " << *minmax_pressure.first << " bar" << endl;
		cout << "Max pressure: " << *minmax_pressure.second << " bar" << endl;

		cout << "High pressure values (>8 bar): ";
		for_each(pressure.begin(), pressure.end(),
			[](double x) { if (x > 8) cout << x << " "; });


		// задание 14
		vector<double> power_energy(24);
		cout << "Write 24 hourly energy consumption values (100-500 kWh)" << endl;
		for (int i = 0; i < 24; i++) {
			cin >> power_energy[i];
		};

		cout << "Hourly energy consumption: ";
		for_each(power_energy.begin(), power_energy.end(), [](double x) {cout << x << " "; });

		double total_consumption = accumulate(power_energy.begin(), power_energy.end(), 0.0);
		double avg_consumption = total_consumption / 24;
		cout << " " << endl;
		cout << "Total daily consumption: " << total_consumption << " kWh" << endl;
		cout << "Average hourly consumption: " << avg_consumption << " kWh" << endl;

		auto peak_hour = max_element(power_energy.begin(), power_energy.end());
		int peak_index = distance(power_energy.begin(), peak_hour);
		cout << "Peak consumption hour: " << peak_index << " (" << *peak_hour << " kWh)" << endl;

		vector<double> deviations(24);
		transform(power_energy.begin(), power_energy.end(), deviations.begin(),
			[avg_consumption](double x) { return x - avg_consumption; });

		cout << "Deviations from average: ";
		for_each(deviations.begin(), deviations.end(), [](double x) {cout << x << " "; });

		vector<double> sorted_consumption = power_energy;
		sort(sorted_consumption.begin(), sorted_consumption.end());
		cout << " " << endl;
		cout << "Top 5 minimum consumption hours: ";
		for (int i = 0; i < 5; i++) {
			cout << sorted_consumption[i] << " ";
		}

		// задание 15
		vector<vector<double>> temp(5, vector<double>(30));
		vector<vector<double>> pressure(5, vector<double>(100));

		cout << "Enter temperature data for 5 channels (30 measurements each):" << endl;
		for (int i = 0; i < 5; i++) {
			cout << "Channel " << i + 1 << " temperatures: ";
			for (int j = 0; j < 30; j++) {
				cin >> temp[i][j];
			}
		}

		cout << "Enter pressure data for 5 channels (100 measurements each):" << endl;
		for (int i = 0; i < 5; i++) {
			cout << "Channel " << i + 1 << " pressures: ";
			for (int j = 0; j < 100; j++) {
				cin >> pressure[i][j];
			}
		}

		vector<double> avg_temperatures(5);
		for (int i = 0; i < 5; i++) {
			double sum = accumulate(temp[i].begin(), temp[i].end(), 0.0);
			avg_temperatures[i] = sum / temp[i].size();
			cout << "Average temperature channel " << i + 1 << ": " << avg_temperatures[i] << endl;
		}

		vector<pair<double, double>> pressure_minmax(5);
		for (int i = 0; i < 5; i++) {
			auto minmax = minmax_element(pressure[i].begin(), pressure[i].end());
			pressure_minmax[i] = { *minmax.first, *minmax.second };
			cout << "Channel " << i + 1 << " pressure range: " << *minmax.first << " - " << *minmax.second << endl;
		}

		vector<vector<double>> temp_differences(5, vector<double>(29));
		for (int i = 0; i < 5; i++) {
			transform(temp[i].begin() + 1, temp[i].end(), temp[i].begin(), temp_differences[i].begin(),
				[](double a, double b) { return a - b; });
		}

		vector<double> temp_variations(5);
		for (int i = 0; i < 5; i++) {
			auto minmax = minmax_element(temp[i].begin(), temp[i].end());
			temp_variations[i] = *minmax.second - *minmax.first;
		}
		auto max_var = max_element(temp_variations.begin(), temp_variations.end());
		int max_var_channel = distance(temp_variations.begin(), max_var);
		cout << "Channel with max temperature variation: " << max_var_channel + 1 << endl;

		vector<vector<double>> normalized_pressure(5, vector<double>(100));
		for (int i = 0; i < 5; i++) {
			double min_p = pressure_minmax[i].first;
			double max_p = pressure_minmax[i].second;
			transform(pressure[i].begin(), pressure[i].end(), normalized_pressure[i].begin(),
				[min_p, max_p](double x) { return (x - min_p) / (max_p - min_p); });
		}

		cout << "Pressure peaks (>0.9 after normalization):" << endl;
		for (int i = 0; i < 5; i++) {
			cout << "Channel " << i + 1 << ": ";
			for_each(normalized_pressure[i].begin(), normalized_pressure[i].end(),
				[](double x) { if (x > 0.9) cout << x << " "; });
			cout << endl;
		}

		vector<int> channel_indexes(5);
		iota(channel_indexes.begin(), channel_indexes.end(), 0);
		sort(channel_indexes.begin(), channel_indexes.end(),
			[&avg_temperatures](int a, int b) { return avg_temperatures[a] > avg_temperatures[b]; });

		cout << "Channel with highest average temperature: " << channel_indexes[0] + 1 << endl;
	return 0;
}
