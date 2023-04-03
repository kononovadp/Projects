let ac = {
  chr: null,
   cmin: null,
    csec: null,

  
  thr: null,
   thm: null,
    ths: null,
  tset: null,
   treset: null,

  // (A3) ВРЕМЯ БУДИЛЬНИКА И ЗВУК
  alarm: null,
   sound: null,

  // (B) ИНИЦИАЛИЗАЦИЯ БУДИЛЬНИКА
  init: () => {
  
    ac.chr = document.getElementById("chr");
    ac.cmin = document.getElementById("cmin");
    ac.csec = document.getElementById("csec");
	nap=document.getElementById("header1");

    // (B2) СОЗДАТЬ ИНСТРУМЕНТ ВРЕМЕНИ HTML – ЧАСЫ, МИН., СЕК.
    ac.thr = ac.createSel(23);
    ac.thm = ac.createSel(59);
    ac.ths = ac.createSel(59);
    document.getElementById("tpick-h").appendChild(ac.thr);
    document.getElementById("tpick-m").appendChild(ac.thm);
    document.getElementById("tpick-s").appendChild(ac.ths);

    // (B3) CREATE HTML TIME PICKER - SET, RESET
    ac.tset = document.getElementById("tset");
    ac.treset = document.getElementById("treset");
    ac.tset.onclick = ac.set;
    ac.treset.onclick = ac.reset;

    // (B4) СИГНАЛ БУДИЛЬНИКА
    ac.sound = new Audio("wake-up-sound.mp3");

    // (B5) НАЧАТЬ ЧАСЫ
    ac.alarm = null;
    setInterval(ac.tick, 1000);
  },

  // (C) ФУНКЦИЯ ПОДДЕРЖКИ - СОЗДАТЬ СЕЛЕКТОР ДЛЯ ЧАСОВ, МИН, СЕК
  createSel : max => {
    let selector = document.createElement("select"), opt;
    for (let i=0; i<=max; i++) {
      opt = document.createElement("option");
      i = ac.padzero(i);
      opt.value = i;
      opt.innerHTML = i;
      selector.appendChild(opt);
    }
    return selector;
  },

  // (D) ФУНКЦИЯ ПОДДЕРЖКИ - ПРЕДВАРИТЕЛЬНАЯ ПОДДЕРЖКА ЧАСОВ, МИН, СЕК С 0 (ЕСЛИ < 10)
  padzero : num => {
    if (num < 10) { num = "0" + num; }
    else { num = num.toString(); }
    return num;
  },

  // (E) ОБНОВИТЬ ТЕКУЩЕЕ ВРЕМЯ
  tick : () => {
    // (E1) ТЕКУЩЕЕ ВРЕМЯ
    let now = new Date(),
        hr = ac.padzero(now.getHours()),
        min = ac.padzero(now.getMinutes()),
        sec = ac.padzero(now.getSeconds());

    // (E2) ОБНОВИТЬ ЧАСЫ HTML
    ac.chr.innerHTML = hr;
    ac.cmin.innerHTML = min;
    ac.csec.innerHTML = sec;

    // (E3) ПРОВЕРКА И ЗВУКОВАЯ СИГНАЛИЗАЦИЯ
    if (ac.alarm != null) {
      now = hr + min + sec;
      if (now == ac.alarm && ac.sound.paused) { ac.sound.play(); }
    }
  },

  // (F) УСТАНОВИТЬ БУДИЛЬНИК
  set : () => {
    ac.alarm = ac.thr.value + ac.thm.value + ac.ths.value;
    ac.thr.disabled = true;
    ac.thm.disabled = true;
    ac.ths.disabled = true;
    ac.tset.disabled = true;
    ac.treset.disabled = false;
	nap.textContent='Будильник встановлено на ';
	
  },

  // (G) СБРОС БУДИЛЬНИКА
  reset : () => {
    if (!ac.sound.paused) { ac.sound.pause(); }
    ac.alarm = null;
    ac.thr.disabled = false;
    ac.thm.disabled = false;
    ac.ths.disabled = false;
    ac.tset.disabled = false;
    ac.treset.disabled = true;
	nap.textContent='ВСТАНОВИТИ БУДИЛЬНИК';
  }
};

// (H) ЗАПУСК ЧАСОВ ПРИ ЗАГРУЗКЕ СТРАНИЦЫ
window.addEventListener("load", ac.init);