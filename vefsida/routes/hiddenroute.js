var express = require('express');
var router = express.Router();

/* GET home page. */
router.get('/', function(req, res, next) {
  res.render('hiddenroute', { title: 'Dagbók' });
});

module.exports = router;
