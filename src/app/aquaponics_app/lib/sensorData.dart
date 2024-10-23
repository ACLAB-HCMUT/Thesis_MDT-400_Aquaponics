// sensor_data.dart
import 'dart:convert';
import 'package:http/http.dart' as http;

class SensorData {
  double temperature = 0.0;
  double humidity = 0.0;
  double pH = 7.0;
  double dO = 0.0;

  final String username;
  final String apiKey;

  SensorData(this.username, this.apiKey);

  Future<void> fetchData() async {
    // try {
    //   final tempData = await _fetchFeed('temperature');
    //   final humidityData = await _fetchFeed('humidity');
    //   final pHData = await _fetchFeed('pH');
    //   final dOData = await _fetchFeed('DO');

    //   temperature = double.parse(tempData);
    //   humidity = double.parse(humidityData);
    //   pH = double.parse(pHData);
    //   dO = double.parse(dOData);
    // } catch (e) {
    //   print('Error fetching data: $e');
    // }
  }

  Future<String> _fetchFeed(String feedName) async {
    final url = 'https://io.adafruit.com/api/v2/$username/feeds/$feedName/data';
    final headers = {
      'X-AIO-Key': apiKey,
      'Content-Type': 'application/json',
    };

    final response = await http.get(Uri.parse(url), headers: headers);

    if (response.statusCode == 200) {
      final List<dynamic> data = json.decode(response.body);
      return data.first['value'];
    } else {
      throw Exception('Failed to load data');
    }
  }
}
