import 'package:aquaponics_app/sensorData.dart';
import 'package:flutter/material.dart';
import 'package:shared_preferences/shared_preferences.dart';
// PAGES
import 'loginPage.dart';
import 'sensorInfo.dart';

class HomeScreen extends StatefulWidget {
  const HomeScreen({super.key});

  @override
  State<HomeScreen> createState() => HomeScreenState();
}

class HomeScreenState extends State<HomeScreen> {
  final SensorData sensorData = SensorData("phongcute", "");

  @override
  void initState() {
    super.initState();
    // Simulate fetching sensor data
    fetchSensorData();
  }

  void fetchSensorData() async {
    await sensorData.fetchData();
    setState(() {});
  }

  Future<void> logout() async {
    final navigator = Navigator.of(context);
    SharedPreferences preferences = await SharedPreferences.getInstance();
    preferences.remove('isLoggedIn');
    navigator.pushReplacement(
      MaterialPageRoute(builder: (context) => const LoginScreen()),
    );
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        leading: Builder(
          builder: (BuildContext context) {
            return IconButton(
              icon: Icon(Icons.menu),
              onPressed: () {
                Scaffold.of(context).openDrawer();
              },
            );
          },
        ),
        title: Container(
          width: 200,
          height: 48,
          child: ElevatedButton(
            onPressed: () {
              // Button action
            },
            child: Row(
              mainAxisAlignment: MainAxisAlignment.center,
              children: [
                Icon(Icons.energy_savings_leaf),
                SizedBox(width: 16), // Adjust spacing if necessary
                Text(
                  'Aquaponics',
                  style: TextStyle(fontSize: 18),
                ),
              ],
            ),
          ),
        ),
        centerTitle: true,
      ),

      drawer: Drawer(
        child: ListView(
          padding: EdgeInsets.zero,
          children: <Widget>[
            DrawerHeader(
              decoration: BoxDecoration(
                color: Colors.blue,
              ),
              child: Text(
                'Menu',
                style: TextStyle(
                  color: Colors.white,
                  fontSize: 24,
                ),
              ),
            ),
            ListTile(
              leading: Icon(Icons.house),
              title: Text('House'),
              onTap: () {
                // Handle the Home action
              },
            ),
            ListTile(
              leading: const Icon(Icons.water),
              title: const Text('Pumps'),
              onTap: () {
                // Handle the Home action
              },
            ),
            ListTile(
              leading: const Icon(Icons.thermostat),
              title: const Text('Sensors'),
              onTap: () {
                // Handle the Settings action
              },
            ),
            ListTile(
              leading: const Icon(Icons.exit_to_app),
              title: const Text('Logout'),
              onTap: () {
                logout();
                // Handle the Logout action
              },
            ),
          ],
        ),
      ),

      body: Padding(
        padding: const EdgeInsets.all(16.0),
        child: Container(
          child: Column(
            mainAxisAlignment: MainAxisAlignment.center,
            children: [
              Expanded(
                child: const Placeholder(),
              ),
              Expanded(
                child: Row(
                    children: [
                      Expanded(
                        child: Container(
                          child: const Placeholder(),
                        ),
                      ),
                      Expanded(
                        child: Container(
                          color: Colors.grey[25],
                          child: Column(
                            mainAxisAlignment: MainAxisAlignment.center,
                            children: [
                              Expanded(
                                child:  SensorInfo(
                                  name: 'Temperature',
                                  value: '${sensorData.temperature} °C',
                                  icon: Icons.thermostat,
                                  color: Colors.yellow,
                                  isConnected: true,
                                ),
                              ),
                              Expanded(
                                child:  SensorInfo(
                                  name: 'Humidity',
                                  value: '${sensorData.humidity} %',
                                  icon: Icons.water_drop,
                                  color: Colors.green,
                                  isConnected: true
                                ),
                              ),
                              Expanded(
                                child: SensorInfo(
                                  name: 'pH',
                                  value: '${sensorData.pH} pH',
                                  icon: Icons.pie_chart,
                                  color: Colors.red,
                                  isConnected: true
                                ),
                              ),
                              Expanded(
                                child: SensorInfo(
                                  name: 'DO',
                                  value: '${sensorData.dO} DO',
                                  icon: Icons.air,
                                  color: Colors.lightBlue,
                                  isConnected: true
                                )
                              )
                            ],
                          ),
                        ),
                      ),
                    ]
                ),
              ),
              Expanded(
                child: const Placeholder(),
              ),
            ],
          )
        ),
      ),
    );
  }
}