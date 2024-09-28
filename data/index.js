const userName = "phongcute";

const base_url = `https://io.adafruit.com/api/v2/${userName}/feeds`;

const tempContainer = document.getElementById("temperatue-value");
const humiContainer = document.getElementById("humidity-value");

const getSensorValue = async (feedKey, container) => {
  fetch(base_url + `/${feedKey}/data?limit=1`, {
    headers: {
      "X-AIO-Key": "",
    },
    method: "GET",
  })
    .then((response) => {
      {
        if (!response.ok) {
          throw new Error("Network response was not ok");
        }
        return response.json();
      }
    })
    .then((data) => {
      container.innerText = data[0].value;
    });
};

setInterval(() => {
  getSensorValue("temp", tempContainer);
  getSensorValue("humi", humiContainer);
}, 5000);
