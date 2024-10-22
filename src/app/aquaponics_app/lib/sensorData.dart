import 'package:flutter/material.dart';
import 'package:shared_preferences/shared_preferences.dart';

class SensorInfo extends StatelessWidget {
  final String name;
  final String value;
  final IconData icon;
  final Color color;
  final bool isConnected;

  const SensorInfo({
    super.key,
    required this.name,
    required this.value,
    required this.icon,
    required this.color,
    required this.isConnected,
  });

  @override
  Widget build(BuildContext context) {
    return Card(
        color: isConnected ? Colors.grey[15] : Colors.black,
        child: ListTile(
          leading: Icon(icon, color: color),
          title: Text(name),
          subtitle: Text('Value: $value'),
          trailing: Icon(isConnected ? Icons.check_circle : Icons.error, color: isConnected ? Colors.green : Colors.red),
        ),
    );
  }
}