<template>
  <div class="compass">
    <div class="compass-inner">
      <div class="north">N</div>
      <div class="east">E</div>
      <div class="west">W</div>
      <div class="south">S</div>
      <div
        class="main-arrow"
        :style="{
                  '-webkit-transform': 'rotate('+heading+'deg)'
                  }"
      >
        <div class="arrow-up"></div>
        <div class="arrow-down"></div>
      </div>
    </div>
  </div>
</template>

<script>
export default {
  name: 'Compass',
  props: {
    heading: {
      type: Number,
      default: 10,
    },
  },
  data () {
    return {
    };
  },
}
</script>

<style lang="scss" scoped>
.compass {
  width: 400px;
  height: 400px;
  background-color: #f3f3f3;
  border-radius: 100%;
  background-image: -webkit-linear-gradient(top, #f7f7f7, #ececec);
  position: relative;
  margin: 0 auto;
}

.compass-inner {
  width: 340px;
  height: 340px;
  background-color: #3d3d3d;
  border-radius: 100%;
  position: relative;
  left: 27.5px;
  top: 27.5px;
  border: 3px solid #c5c5c5;
}

.main-arrow {
  height: 100%;
  width: 30px;
  left: 155px;
  position: relative;
  padding-top: 5px;
  box-sizing: border-box;
  transform: rotate(20deg);
  transition: all 0.5s ease-in-out;
  // animation: spin 2s alternate infinite;
  // -ms-transform: rotate(20deg);
  // -o-transform: rotate(20deg);
  // -o-animation: spin 2s alternate infinite;
  // -moz-transform: rotate(20deg);
  // -moz-animation: spin 2s alternate infinite;
  // -webkit-transform: rotate(20deg);
  // -webkit-animation: spin 2s alternate infinite;
}

.arrow-up {
  width: 0;
  height: 0;
  border-left: 15px solid transparent;
  border-right: 15px solid transparent;
  border-bottom: 165px solid #ef5052;
  position: relative;
}

.arrow-down {
  -webkit-transform: rotate(180deg); /* Safari and Chrome */
  width: 0;
  transform: rotate(180deg);
  -ms-transform: rotate(180deg);
  height: 0;
  border-left: 15px solid transparent;
  border-right: 15px solid transparent;
  border-bottom: 165px solid #f3f3f3;
  position: relative;
}

.north {
  font-size: 36px;
  font-family: "Lobster Two", cursive;
  color: #fff;
  position: absolute;
  left: 155px;
  top: 10px;
}

.east {
  font-size: 36px;
  font-family: "Lobster Two", cursive;
  color: #fff;
  position: absolute;
  left: 290px;
  top: 150px;
}

.west {
  font-size: 36px;
  font-family: "Lobster Two", cursive;
  color: #fff;
  position: absolute;
  left: 20px;
  top: 150px;
}

.south {
  font-size: 36px;
  font-family: "Lobster Two", cursive;
  color: #fff;
  position: absolute;
  left: 155px;
  top: 280px;
}

@keyframes spin {
  0% {
    transform: scale(1) rotate(0deg);
  }
  50% {
    transform: scale(1) rotate(80deg);
  }
  100% {
    transform: scale(1) rotate(-180deg);
  }
}

@-o-keyframes spin {
  0% {
    -webkit-transform: scale(1) rotate(0deg);
  }
  50% {
    -webkit-transform: scale(1) rotate(80deg);
  }
  100% {
    -webkit-transform: scale(1) rotate(-180deg);
  }
}

@-moz-keyframes spin {
  0% {
    -webkit-transform: scale(1) rotate(0deg);
  }
  50% {
    -webkit-transform: scale(1) rotate(80deg);
  }
  100% {
    -webkit-transform: scale(1) rotate(-180deg);
  }
}

@-webkit-keyframes spin {
  0% {
    -webkit-transform: scale(1) rotate(0deg);
  }
  50% {
    -webkit-transform: scale(1) rotate(80deg);
  }
  100% {
    -webkit-transform: scale(1) rotate(-180deg);
  }
}

@media (max-width: 600px) {
  .compass {
    width: 200px;
    height: 200px;
    text-align: center;
  }

  .compass-inner {
    width: 170px;
    height: 170px;
    left: 13px;
    top: 13px;
  }

  .main-arrow {
    width: 30px;
    left: 78px;
    width: 15px;
    padding-top: 3px;
  }

  .arrow-up {
    border-bottom: 82.5px solid #ef5052;
    border-left: 7.5px solid transparent;
    border-right: 7.5px solid transparent;
  }

  .arrow-down {
    border-bottom: 82.5px solid #f3f3f3;
    border-left: 7.5px solid transparent;
    border-right: 7.5px solid transparent;
  }

  .north {
    left: 78px;
    top: 10px;
    font-size: 16px;
  }

  .south {
    font-size: 16px;
    left: 78px;
    top: 140px;
  }

  .east {
    font-size: 16px;
    top: 72.5px;
    left: 145px;
  }

  .west {
    font-size: 16px;
    left: 10px;
    top: 72.5px;
  }
}

@media (max-width: 600px) {
  .compass {
    width: 200px;
    height: 200px;
    text-align: center;
  }

  .compass-inner {
    width: 170px;
    height: 170px;
    left: 13px;
    top: 13px;
  }

  .main-arrow {
    width: 30px;
    left: 78px;
    width: 15px;
    padding-top: 3px;
  }

  .arrow-up {
    border-bottom: 82.5px solid #ef5052;
    border-left: 7.5px solid transparent;
    border-right: 7.5px solid transparent;
  }

  .arrow-down {
    border-bottom: 82.5px solid #f3f3f3;
    border-left: 7.5px solid transparent;
    border-right: 7.5px solid transparent;
  }

  .north {
    left: 78px;
    top: 10px;
    font-size: 16px;
  }

  .south {
    font-size: 16px;
    left: 78px;
    top: 140px;
  }

  .east {
    font-size: 16px;
    top: 72.5px;
    left: 145px;
  }

  .west {
    font-size: 16px;
    left: 10px;
    top: 72.5px;
  }
}

@media (max-width: 600px) {
  .compass {
    width: 200px;
    height: 200px;
    text-align: center;
  }

  .compass-inner {
    width: 170px;
    height: 170px;
    left: 13px;
    top: 13px;
  }

  .main-arrow {
    width: 30px;
    left: 78px;
    width: 15px;
    padding-top: 3px;
  }

  .arrow-up {
    border-bottom: 82.5px solid #ef5052;
    border-left: 7.5px solid transparent;
    border-right: 7.5px solid transparent;
  }

  .arrow-down {
    border-bottom: 82.5px solid #f3f3f3;
    border-left: 7.5px solid transparent;
    border-right: 7.5px solid transparent;
  }

  .north {
    left: 78px;
    top: 10px;
    font-size: 16px;
  }

  .south {
    font-size: 16px;
    left: 78px;
    top: 140px;
  }

  .east {
    font-size: 16px;
    top: 72.5px;
    left: 145px;
  }

  .west {
    font-size: 16px;
    left: 10px;
    top: 72.5px;
  }
}

@media (max-width: 600px) {
  .compass {
    width: 200px;
    height: 200px;
    text-align: center;
  }

  .compass-inner {
    width: 170px;
    height: 170px;
    left: 13px;
    top: 13px;
  }

  .main-arrow {
    width: 30px;
    left: 78px;
    width: 15px;
    padding-top: 3px;
  }

  .arrow-up {
    border-bottom: 82.5px solid #ef5052;
    border-left: 7.5px solid transparent;
    border-right: 7.5px solid transparent;
  }

  .arrow-down {
    border-bottom: 82.5px solid #f3f3f3;
    border-left: 7.5px solid transparent;
    border-right: 7.5px solid transparent;
  }

  .north {
    left: 78px;
    top: 10px;
    font-size: 16px;
  }

  .south {
    font-size: 16px;
    left: 78px;
    top: 140px;
  }

  .east {
    font-size: 16px;
    top: 72.5px;
    left: 145px;
  }

  .west {
    font-size: 16px;
    left: 10px;
    top: 72.5px;
  }
}
</style>