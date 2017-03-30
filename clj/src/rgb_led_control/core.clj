(ns rgb-led-control.core
  (:require [serial.core :as serial]
            [clojure.tools.logging :as log]))

(def serial-port
  (let [port (serial/open "/dev/ttyUSB0")]
    (Thread/sleep 2000) ;; 1000  was too small, 2000 works. don't know why
    port))

;; colors
(def black [0 0 0])
(def rose [19 6 9])
(def pink [59 4 21])
(def purple [38 8 60])
(def yellow [26 25 4])
(def light-green [4 36 15])

(defn set-pixel [port number]
  (serial/write port number))

(defn set-color [port rgb]
  (serial/write port (first rgb))
  (serial/write port (second rgb))
  (serial/write port (last rgb)))

(defn set-stop-byte [port]
  (serial/write port 255)
  (Thread/sleep 1))

(defn set-pixel-color [port pixel rgb]
  (set-pixel port pixel)
  (set-color port rgb)
  (set-stop-byte port))

(defn turn-off []
  (dotimes [i 24]
    (set-pixel-color serial-port i black)))

(defn make-circle [color]
  (dotimes [i 24]
    (set-pixel-color serial-port i color)
    (Thread/sleep 100)))

(defn -main [& args])
