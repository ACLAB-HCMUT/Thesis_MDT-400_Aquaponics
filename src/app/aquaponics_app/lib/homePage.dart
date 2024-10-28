import 'package:flutter/material.dart';
import 'package:shared_preferences/shared_preferences.dart';
// PAGES
import 'loginPage.dart';
import 'sensorData.dart';
import 'sensorInfo.dart';

class HomeScreen extends StatefulWidget {
  const HomeScreen({super.key});

  @override
  State<HomeScreen> createState() => HomeScreenState();
}

class HomeScreenState extends State<HomeScreen> {
  final SensorData sensorData = SensorData("phongcute", "");
  int _currentIndex = 0; // Chỉ số để theo dõi trang hiện tại

  @override
  void initState() {
    super.initState();
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
            onPressed: () {},
            child: Row(
              mainAxisAlignment: MainAxisAlignment.center,
              children: [
                Icon(Icons.energy_savings_leaf),
                SizedBox(width: 16),
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
              decoration: BoxDecoration(color: Colors.blue),
              child: Text(
                'Menu',
                style: TextStyle(color: Colors.white, fontSize: 24),
              ),
            ),
            ListTile(
              leading: Icon(Icons.house),
              title: Text('House'),
              onTap: () {},
            ),
            ListTile(
              leading: Icon(Icons.water),
              title: Text('Pumps'),
              onTap: () {},
            ),
            ListTile(
              leading: Icon(Icons.thermostat),
              title: Text('Sensors'),
              onTap: () {},
            ),
            ListTile(
              leading: Icon(Icons.exit_to_app),
              title: Text('Logout'),
              onTap: logout,
            ),
          ],
        ),
      ),
      body:
          _getSelectedPage(_currentIndex), // Gọi hàm để hiển thị trang hiện tại
      bottomNavigationBar: BottomNavigationBar(
        currentIndex: _currentIndex,
        onTap: (index) {
          setState(() {
            _currentIndex = index;
          });
        },
        selectedItemColor: Colors.blue, // Màu cho tab đang được chọn
        unselectedItemColor: Colors.black, // Màu cho các tab chưa chọn
        type:
            BottomNavigationBarType.fixed, // Để cố định vị trí của icon và text
        items: const [
          BottomNavigationBarItem(
            icon: Icon(Icons.home),
            label: 'Home',
          ),
          BottomNavigationBarItem(
            icon: Icon(Icons.analytics),
            label: 'Analysis',
          ),
          BottomNavigationBarItem(
            icon: Icon(Icons.settings),
            label: 'Setting',
          ),
          BottomNavigationBarItem(
            icon: Icon(Icons.devices),
            label: 'Device',
          ),
        ],
      ),
    );
  }

  // Hàm trả về trang dựa trên chỉ số hiện tại
  Widget _getSelectedPage(int index) {
    switch (index) {
      case 0:
        return _buildHomePage();
      case 1:
        return Center(child: Text('Analysis Page'));
      case 2:
        return Center(child: Text('Settings Page'));
      case 3:
        return Center(child: Text('Device Page'));
      default:
        return _buildHomePage();
    }
  }

  // Hàm tạo trang chính Home với thông tin cảm biến
  Widget _buildHomePage() {
    return Padding(
      padding: const EdgeInsets.all(16.0),
      child: Column(
        children: [
          Expanded(
            child: Row(
              mainAxisAlignment: MainAxisAlignment.spaceEvenly,
              children: [
                Expanded(
                  flex: 2,
                  child: AspectRatio(
                    aspectRatio: 1.2,
                    child: SensorInfo(
                      name: 'Temperature',
                      value: '${sensorData.temperature} °C',
                      icon: Icons.thermostat,
                      color: Colors.orange,
                      isConnected: true,
                    ),
                  ),
                ),
                SizedBox(width: 16),
                Expanded(
                  flex: 2,
                  child: AspectRatio(
                    aspectRatio: 1.2,
                    child: SensorInfo(
                      name: 'Humidity',
                      value: '${sensorData.humidity} %',
                      icon: Icons.water_drop,
                      color: Colors.blue,
                      isConnected: true,
                    ),
                  ),
                ),
              ],
            ),
          ),
          SizedBox(height: 16),
          Expanded(
            child: Row(
              mainAxisAlignment: MainAxisAlignment.spaceEvenly,
              children: [
                Expanded(
                  flex: 2,
                  child: AspectRatio(
                    aspectRatio: 1.2,
                    child: SensorInfo(
                      name: 'pH',
                      value: '${sensorData.pH} pH',
                      icon: Icons.pie_chart,
                      color: Colors.green,
                      isConnected: true,
                    ),
                  ),
                ),
                SizedBox(width: 16),
                Expanded(
                  flex: 2,
                  child: AspectRatio(
                    aspectRatio: 1.2,
                    child: SensorInfo(
                      name: 'DO',
                      value: '${sensorData.dO} mg/L',
                      icon: Icons.air,
                      color: Colors.purple,
                      isConnected: true,
                    ),
                  ),
                ),
              ],
            ),
          ),
        ],
      ),
    );
  }
}
