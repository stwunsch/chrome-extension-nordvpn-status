function update() {
  var data = chrome.extension.getBackgroundPage().data;
  if (data && data.success) {
    document.getElementById('Status').innerHTML = data['Status'];
    if (data['Status'] == 'Connected') {
      document.getElementById('Current server').innerHTML = data['Current server'];
      document.getElementById('Country').innerHTML = data['Country'];
      document.getElementById('City').innerHTML = data['City'];
      document.getElementById('Your new IP').innerHTML = data['Your new IP'];
      document.getElementById('Current technology').innerHTML = data['Current technology'];
      document.getElementById('Transfer').innerHTML = data['Transfer'];
      document.getElementById('Uptime').innerHTML = data['Uptime'];
    } else {
      document.getElementById('Current server').innerHTML = '';
      document.getElementById('Country').innerHTML = '';
      document.getElementById('City').innerHTML = '';
      document.getElementById('Your new IP').innerHTML = '';
      document.getElementById('Current technology').innerHTML = '';
      document.getElementById('Transfer').innerHTML = '';
      document.getElementById('Uptime').innerHTML = '';
    }
  } else if (data && !data.success){
    document.getElementById('Status').innerHTML = "Failure (" + data['what'] + ")";
  } else {
    document.getElementById('Status').innerHTML = "Failure (no data from native host)";
  }
  setTimeout(update, 2000);
}

document.addEventListener('DOMContentLoaded', function() {
  update();
});
